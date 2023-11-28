#include <vector>
#include <string>
#include <commands/CommandsUtils.hpp>
#include <utils/Bid.hpp>
#include <utils/Card.hpp>

namespace commands
{


/// @brief Functions splits command into vector of string and returns first element
/// which should be a command type
/// @param command - command to split
/// @param command_data - vector for result
/// @return command type
std::string parseCommand(std::string command, std::vector<std::string>& command_data)
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

/// @brief Generates bid from command_data
/// @param command_data - split command
/// @return bid created from command
/// bid command should have format:
/// BID [ PLAYER_NAME ] SUIT/NT [ x ]
/// where x is planned deal
utils::Bid parseBidCommand(std::vector<std::string>& command_data)
{
    return utils::Bid();
}

/// @brief Generates Card object from command_data
/// @param command_data - split command
/// @return Card created from command
/// bid command should have format:
/// PLAY [ PLAYER_NAME ] [CLUBS/DIAMONDS/HEARST/SPADES] [1..10/JACK/QUEEN/KING/ACE]
utils::Card parsePlayCommand(std::vector<std::string>& command_data)
{
    return utils::Card();
}

};
