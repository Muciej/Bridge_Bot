#include <vector>
#include <stdexcept>
#include <GameEngine/GameManager.hpp>
#include <commands/CommandsUtils.hpp>
#include <commands/CommandCreator.hpp>
#include <utils/Exceptions.hpp>
#include <utils/MoveCorrectnessChecker.hpp>

/// @brief
namespace game
{

using exception::InvalidActionInCurrentStateException;
using exception::WrongCommandException;
using exception::WrongPlayerNumberException;

void GameManager::infoPrint(const std::string& msg)
{
    if(shouldPrintInfo) std::cout << msg << std::endl;
}

/// @brief Main game loop
void GameManager::gameLoop()
{
    std::vector<std::string> command_data;
    std::string command_type;
    while(game.state != GameState::END)
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
        else if(command_type == "DUMMY_PLAY")
            playerDummyMove(command_data);
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
            server->sendToAllClients(command_creator.serverGetSetPositionCommand(command_data[1], players[pos].position));
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
    if(!isCommandLegal(4, GameState::BIDDING, commands::getPositionFromString(command_data[1]), command_data))
    {
        return;
    }

    // all wrong situations checked, bid can be placed
    const auto bid = commands::parseBidCommand(command_data);
    if(!bidding.addBid(commands::getPositionFromString(command_data[1]), bid))
    {
        std::string reply = command_creator.serverGetErrorMsgCommand(commands::getPositionFromString(command_data[1]), "Illegal bid!");
        server->sendToAllClients(reply);
    } else
    {
        std::string reply = command_creator.getBidInfoCommand(commands::getPositionFromString(command_data[1]), bid);
        server->sendToAllClients(reply);
        updateNowMoving();
    }

    if(bidding.isBiddingEnded())
    {
        startGame();
    }
}

void GameManager::playerMove(std::vector<std::string>& command_data)
{
    if(!isCommandLegal(3, GameState::PLAYING, commands::getPositionFromString(command_data[1]), command_data))
        return;

    const auto card = commands::parsePlayCommand(command_data);

    if(!utils::isMoveLegal(players[game.now_moving], card, game.getCurentTrick()))
    {
        std::string reply = command_creator.serverGetErrorMsgCommand(commands::getPositionFromString(command_data[1]), "You cannot play this card!");
        server->sendToAllClients(reply);
        return;
    }

    players[game.now_moving].drawCard(card);
    if(game.now_moving == game.getCurentTrick().first)
    {
        game.tricks[game.current_trick].suit = card.suit;
    }
    server->sendToAllClients(command_creator.getPlayCommand(commands::getPositionFromString(command_data[1]), card));
    infoPrint(command_creator.getPlayCommand(commands::getPositionFromString(command_data[1]), card));
    updateNowMoving();
    if (!game.dummy_card_revealed)
    {
        revealDummysCards();
        game.dummy_card_revealed = true;
    }
    if (game.getCurentTrick().first == game.now_moving) // trick is ended
    {
        utils::setWinner(game.tricks[game.current_trick], game.contract.trump);
        server->sendToAllClients(command_creator.serverGetTrickResultCommand(game.getCurentTrick().winner));
        game.now_moving = game.getCurentTrick().winner;
        game.current_trick++;
    }
    if(game.current_trick == 13)  // game end
    {
        endGame();
    } else
    {
        game.tricks[game.current_trick].first = game.now_moving;
        infoPrint("Next trick will be started by: " + game.now_moving);
    }
}

void GameManager::playerDummyMove(std::vector<std::string>& command_data)
{
    if(!isCommandLegal(3, GameState::PLAYING, utils::getPartnerPosition(commands::getPositionFromString(command_data[1])), command_data))
        return;

    const auto card = commands::parsePlayCommand(command_data);

    if(!utils::isMoveLegal(players[game.now_moving], card, game.getCurentTrick()))
    {
        std::string reply = command_creator.serverGetErrorMsgCommand(commands::getPositionFromString(command_data[1]), "You cannot play this card!");
        server->sendToAllClients(reply);
        return;
    }
    players[game.now_moving].drawCard(card);
    if(game.now_moving == game.getCurentTrick().first)
    {
        game.tricks[game.current_trick].suit = card.suit;
    }
    server->sendToAllClients(command_creator.getPlayCommand(commands::getPositionFromString(command_data[1]), card));
    infoPrint(command_creator.getPlayCommand(commands::getPositionFromString(command_data[1]), card));
    updateNowMoving();
    if (game.getCurentTrick().first == game.now_moving) // trick is ended
    {
        utils::setWinner(game.tricks[game.current_trick], game.contract.trump);
        server->sendToAllClients(command_creator.serverGetTrickResultCommand(game.getCurentTrick().winner));
        game.now_moving = game.getCurentTrick().winner;
        game.current_trick++;
    }
    if(game.current_trick == 13)  // game end
    {
        endGame();
    } else
    {
        game.tricks[game.current_trick].first = game.now_moving;
        infoPrint("Next trick will be started by: " + game.now_moving);
    }
}

void GameManager::startBidding()
{
    game.state = GameState::BIDDING;
    infoPrint("All players connected. Bidding has started!");
    bidding.clear();
    game.now_moving = bidder;
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

/// @brief Handles game start after bidding i.e. sets up everything for fist move
void GameManager::startGame()
{
    infoPrint("Bidding has ended, game started!");
    auto contract = bidding.getContract();
    if(!contract)   // 4 passes, game is ended
    {
        endGame();
        return;
    }

    game.contract = bidding.getContract().value();
    game.declarer = bidding.getDeclarer().value();
    game.now_moving = game.declarer;
    updateNowMoving();
    game.current_trick = 0;
    game.tricks[0].first = game.now_moving;
    infoPrint("First trick will be started by: " + game.now_moving);
    server->sendToAllClients(command_creator.serverGetBidEndCommand(game.declarer, game.contract));
    game.state = GameState::PLAYING;
}


/// @brief Checks if the given command represented by command_data vector is legal, i.e.
/// if it has appropriate length, if game is in proper state to process it and if
/// player who sent it is actually the player moving. The function allows declarer to send
/// play command during dummy's round and prevents dummy from moving itself.
/// @param desired_cmd_length - length expected for the command
/// @param required_state - state required to process this command
/// @param player_position - position of player, who placed the command
/// @param command_data - vector of strings (split command)
/// @return - ture if command is legal and false otherwise
bool GameManager::isCommandLegal(int desired_cmd_length, GameState required_state, const utils::Position& player_position, std::vector<std::string>& command_data)
{
    if (game.state != required_state)
    {
        throw InvalidActionInCurrentStateException();
    } else if (!isGameFull())
    {
        throw WrongPlayerNumberException();
    } else if(command_data.size() != static_cast<long unsigned int>(desired_cmd_length))
    {
        throw WrongCommandException();
    } else if (player_position != game.now_moving)
    {
        std::string reply = command_creator.serverGetErrorMsgCommand(player_position, "It's not your move!");
        server->sendToAllClients(reply);
        return false;
    }
    return true;
}

void GameManager::updateNowMoving()
{
    game.now_moving = static_cast<utils::Position>((static_cast<int>(game.now_moving) + 1)%4);
}

void GameManager::updateBidder()
{
    bidder = static_cast<utils::Position>((static_cast<int>(game.now_moving) + 1)%4);
}

/// @brief Handles game end, send info about results and restarts game
void GameManager::endGame()
{
    infoPrint("Game ended, sending score info");
    auto winners = game.getWinners();
    auto score = game.getScore();
    server->sendToAllClients(command_creator.serverGetGameEndCommand(winners.first, winners.second, score));
    game = utils::Game();   // game reset
    if (isGameFull())
    {
        updateBidder();
        startBidding();
    } else
    {
        game.state = GameState::END;
    }
}

/// @brief Sends dummy's cards to every player
void GameManager::revealDummysCards()
{
    server->sendToAllClients(command_creator.serverGetDummyCardInfoCommand(utils::getPartnerPosition(game.declarer), players[utils::getPartnerPosition(game.declarer)].hand));
}

};
