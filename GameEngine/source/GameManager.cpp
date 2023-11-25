#include <GameEngine/GameManager.hpp>
#include <vector>
#include <stdexcept>
#include <commands/CommandsUtils.hpp>

namespace game
{

class WrongCommandException : public std::exception {
    public:
const char * what () {
        std::string msg("Wrong command format!");
        return msg.c_str();
    }
};

class InvalidActionInCurrentStateException : public std::exception {
    public:
const char * what () {
        std::string msg("This action is not permitted in this state!");
        return msg.c_str();
    }
};

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

            bool should_start_bidding = true;
            for(int i = 0; i<4; i++){
                if(!connected_players[i])
                    should_start_bidding = false;
            }
            if(should_start_bidding)
            {
                state = GameState::BIDDING;
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
    command_data.size();
}

void GameManager::playerMove(std::vector<std::string>& command_data)
{
    command_data.size();
}

void GameManager::startBidding()
{
    now_moving = utils::Position::NORTH;
    server->sendToAllClients(command_creator.serverGetStartBiddingCommand(utils::Position::NORTH));
}

};
