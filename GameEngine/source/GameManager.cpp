#include <GameEngine/GameManager.hpp>
#include <vector>
#include <stdexcept>
#include <commands/CommandsUtils.hpp>
#include <commands/CommandCreator.hpp>
#include <utils/Exceptions.hpp>

namespace game
{

using exception::InvalidActionInCurrentStateException;
using exception::WrongCommandException;
using exception::WrongPlayerNumberException;

utils::Position GameManager::getPlayerPosition(std::string name)
{
    for(int i = 0; i<4; i++)
    {
        if(connected_players[i] && players[i].name == name)
        {
            return players[i].position;
        }
    }
    //in case there is no such player
    throw std::runtime_error("There is no player " + name + "!");
}

void GameManager::infoPrint(const std::string& msg)
{
    if(shouldPrintInfo) std::cout << msg << std::endl;
}

/// @brief Main game loop
void GameManager::gameLoop()
{
    std::vector<std::string> command_data;
    std::string command_type;
    while(true)
    {
        command_type = commands::parseCommand(server->popCommandWait(), command_data);
        if(command_data.size() < 2)
        {
            infoPrint("Wrong format of command (too short)!");
            continue;
        }

        if(command_type == "ADD_PLAYER")
            addPlayer(command_data);
        else if(command_type == "PLAY")
            playerMove(command_data);
        else if(command_type == "BID")
            playerBid(command_data);
        else
            throw WrongCommandException();
    }
}

/// @brief Adds new player to the game
/// @param command_data - data from ADD_PLAYER command
void GameManager::addPlayer(std::vector<std::string>& command_data)
{

    if(game.state == GameState::IN_LOBBY && command_data.size() == 3)
    {
        int pos = 0;
        while(pos < 4)
        {
            if (!connected_players[pos])
            {
                break;
            }
            pos ++;
        }
        if(pos == 4)
        {
            throw std::range_error("Cannot add player to a full game!");
        } else
        {
            bool is_bot = command_data.at(2) == "BOT" ? true : false;
            players[pos] = utils::Player(command_data.at(1), utils::Position(pos), is_bot);
            connected_players[pos] = true;
            infoPrint("Player " + command_data.at(1) + " connected!");
            if(isGameFull())
            {
                generateAndSendDeck();
                startBidding();
            }
        }

    } else if (game.state != GameState::IN_LOBBY)
    {
        throw InvalidActionInCurrentStateException();
    } else
    {
        throw WrongCommandException();
    }
}

void GameManager::playerBid(std::vector<std::string>& command_data)
{
    if (game.state != game::GameState::BIDDING)
    {
        throw InvalidActionInCurrentStateException();
    } else if (!isGameFull())
    {
        throw WrongPlayerNumberException();
    } else if (players[static_cast<int>(game.now_moving)].name != command_data[1])
    {
        std::string reply = command_creator.serverGetErrorMsgCommand(getPlayerPosition(command_data[1]), "It's not your move!");
        server->sendToAllClients(reply);
        return;
    }

    // all wrong situations checked, bid can be placed
    auto bid = commands::parseBidCommand(command_data);
    if(!bidding.addBid(getPlayerPosition(command_data[1]), bid))
    {
        std::string reply = command_creator.serverGetErrorMsgCommand(getPlayerPosition(command_data[1]), "Illegal bid!");
        server->sendToAllClients(reply);
    } else
    {
        updateNowMoving();
    }

    if(bidding.isBiddingEnded())
    {
        startGame();
    }
}

void GameManager::playerMove(std::vector<std::string>& command_data)
{
    if(!isCommandLegal(3, GameState::PLAYING, command_data[1]))
        return;

    // sprawdzić, czy gracz ma w ogóle taką kartę
    // sprawdzić, czy ruch legalny w obrębie trwającej lewy
    // wykonać ruch i zaktualizować karty gracza
    // wysłać informację o ruchu do innych graczy
    // zmienić aktualnie ruszającą się osobę
    // jeśli znowu declarer to podbić nr lewy
    // sprawdzić, czy gra się przypadkiem nie skończyła
}

void GameManager::startBidding()
{
    game.state = GameState::BIDDING;
    infoPrint("All players connected. Bidding has started!");
    bidding.clear();
    game.now_moving = utils::Position::NORTH;
    server->sendToAllClients(command_creator.serverGetStartBiddingCommand(utils::Position::NORTH));
}

bool GameManager::isGameFull()
{
    bool game_full = true;
    for(int i = 0; i<4; i++){
        if(!connected_players[i])
            game_full = false;
    }
    return game_full;
}

void GameManager::generateAndSendDeck()
{
    dealer = utils::Dealer();
    auto hands = dealer.dealCards();
    players[0].hand = hands[0];
    players[1].hand = hands[1];
    players[2].hand = hands[2];
    players[3].hand = hands[3];

    server->sendToAllClients(command_creator.serverGetCardsInfoCommand(utils::Position::NORTH, players[utils::Position::NORTH].hand));
    server->sendToAllClients(command_creator.serverGetCardsInfoCommand(utils::Position::WEST, players[utils::Position::WEST].hand));
    server->sendToAllClients(command_creator.serverGetCardsInfoCommand(utils::Position::SOUTH, players[utils::Position::SOUTH].hand));
    server->sendToAllClients(command_creator.serverGetCardsInfoCommand(utils::Position::EAST, players[utils::Position::EAST].hand));
}

void GameManager::startGame()
{
    infoPrint("Bidding has ended, game started!");
    auto contract = bidding.getContract();
    if(!contract)   // 4 passes, game is ended
    {
        // TODO reload game
        return;
    }

    game.contract = bidding.getContract().value();
    game.declarer = bidding.getDeclarer().value();
    game.now_moving = game.declarer;
    server->sendToAllClients(command_creator.serverGetBidEndCommand(game.declarer, game.contract));
    game.state = GameState::PLAYING;
}

bool GameManager::isCommandLegal(int desired_cmd_length, GameState required_state, const std::string& player_name)
{
    if (game.state != required_state)
    {
        throw InvalidActionInCurrentStateException();
    } else if (!isGameFull())
    {
        throw WrongPlayerNumberException();
    } else if (players[static_cast<int>(game.now_moving)].name != player_name)
    {
        std::string reply = command_creator.serverGetErrorMsgCommand(getPlayerPosition(player_name), "It's not your move!");
        server->sendToAllClients(reply);
        return false;
    }

    return true;
}

void GameManager::updateNowMoving()
{
    game.now_moving = static_cast<utils::Position>((static_cast<int>(game.now_moving) + 1)%4);
}

};
