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

    if(state == GameState::IN_LOBBY && command_data.size() == 3)
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
                state = GameState::BIDDING;
                infoPrint("All players connected. Bidding has started!");
                startBidding();
            }
        }

    } else if (state != GameState::IN_LOBBY)
    {
        throw InvalidActionInCurrentStateException();
    } else 
    {
        throw WrongCommandException();
    }
}

void GameManager::playerBid(std::vector<std::string>& command_data)
{
    if (state != game::GameState::BIDDING)
    {
        throw InvalidActionInCurrentStateException();
    } else if (!isGameFull())
    {
        throw WrongPlayerNumberException();
    } else if (players[static_cast<int>(now_moving)].name != command_data[1])
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
    }

    if(bidding.isBiddingEnded())
    {
        state = GameState::PLAYING;
        // ustawić kontrakt w grze
        // wysłać informację o ustawionym kontrakcie
        // wysłać do graczy informacje o tym, kto jest pierwszy
    }
}

void GameManager::playerMove(std::vector<std::string>& command_data)
{

}

void GameManager::startBidding()
{
    bidding.clear();
    now_moving = utils::Position::NORTH;
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

};
