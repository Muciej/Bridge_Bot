#include <commands/CommandsUtils.hpp>
#include <vector>
#include <string>

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

};
