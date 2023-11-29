#pragma once
#include <string>
#include <vector>
#include <utils/Bid.hpp>
#include <utils/Card.hpp>
#include <utils/Player.hpp>

namespace commands
{
    std::string parseCommand(std::string command, std::vector<std::string>& command_data);
    utils::Bid parseBidCommand(std::vector<std::string>& command_data);
    utils::Card parsePlayCommand(std::vector<std::string>& command_data);
    utils::Position parseSetPosCommand(std::vector<std::string>& command_data);

} // namespace command
