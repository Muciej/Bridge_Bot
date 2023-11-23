#include <GameEngine/GameManager.hpp>
#include <vector>
#include <stdexcept>




namespace Game
{

class WrongCommandException : public std::exception {
    public:
char * what () {
        return "Wrong command format!";
    }
};

class InvalidActionInCurrentStateException : public std::exception {
    public:
char * what () {
        return "This action is not permitted in this state!";
    }
};

/// @brief Main game loop
/// @param server - server object, must be started
void GameManager::gameLoop(connection::TcpServer &server)
{
    std::vector<std::string> command_data;
    std::string command_type;
    while(true)
    {
        command_type = parseCommand(server.popCommandWait(), command_data);

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

/// @brief Functions splits command into vector of string and returns first element
/// which should be a command type
/// @param command - command to split
/// @param command_data - vector for result
/// @return command type
std::string GameManager::parseCommand(std::string command, std::vector<std::string>& command_data)
{
    command_data.clear();
    size_t pos;

    while ((pos = command.find(' ')) != std::string::npos) {
        command_data.push_back(command.substr(0, pos));
        command.erase(0, pos + 1);
    }
    if (command.length() > 0)
    {
        command_data.push_back(command);
    }

    return command_data.at(0);
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
            players[pos] = Player(command_data.at(1), Position(pos), is_bot);
            connected_players[pos] = true;
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

}

void GameManager::playerMove(std::vector<std::string>& command_data)
{

}

};
