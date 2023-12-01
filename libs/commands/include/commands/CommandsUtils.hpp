#pragma once
#include <string>
#include <vector>
#include <utils/Bid.hpp>
#include <utils/Card.hpp>
#include <utils/Player.hpp>

namespace commands
{
    utils::Position getPositionFromString(const std::string& name);
    std::string parseCommand(const std::string& command, std::vector<std::string>& command_data);
    utils::Bid parseBidCommand(const std::vector<std::string>& command_data);
    utils::Card parsePlayCommand(const std::vector<std::string>& command_data);
    utils::Position parseSetPosCommand(const std::vector<std::string>& command_data);
    std::vector<utils::Card> parseHandCommand(const std::vector<std::string>& command_data, int cards_start_index);
    utils::Card getCardFromString(const std::string& card_str);

} // namespace command
