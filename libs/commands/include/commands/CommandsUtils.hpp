#pragma once
#include <string>
#include <vector>
#include <utils/Bid.hpp>
#include <utils/Card.hpp>
#include <utils/Player.hpp>

namespace commands
{

    /// @brief Converts string to utils::Position object
    /// @param pos_string - string containing postiion at the table
    /// @return - appropriate utils::Position object
    utils::Position getPositionFromString(const std::string& name);

    /// @brief Functions splits command into vector of string and returns first element
    /// which should be a command type
    /// @param command - command to split
    /// @param command_data - vector for result
    /// @return command type
    std::string parseCommand(const std::string& command, std::vector<std::string>& command_data);

    /// @brief Generates bid from command_data
    /// @param command_data - split command
    /// @return bid created from command
    /// bid command should have format:
    /// BID [ position ] [ trump ] [ deal ]
    /// where trump is one from {NO_TRUMP, PASS, SPADES, HEARTS, DIAMONDS, CLUBS}
    /// and deal is from 1 to 7
    utils::Bid parseBidCommand(const std::vector<std::string>& command_data);

    /// @brief Generates Card object from command_data
    /// @param command_data - split command
    /// @return Card created from command
    /// bid command should have format:
    /// PLAY [ position ] [ card ]
    /// where card is like: ♦5
    utils::Card parsePlayCommand(const std::vector<std::string>& command_data);

    /// @brief Generates position from SETPOS command
    /// @param command_data - split command
    /// @return - Position extracted from command
    /// setpos command should have format:
    /// SETPOS [ name ] [ position ]
    /// where name is any string and position is one of
    /// NORTH/SOUTH/EAST/WEST
    utils::Position parseSetPosCommand(const std::vector<std::string>& command_data);

    /// @brief Generate vector of cards from command
    /// @param command_data - split HAND or DUMMYHAND command
    /// @param cards_start_index - index in command data vector from which cards start
    /// @return - vector of cards extracted from the command
    std::vector<utils::Card> parseHandCommand(const std::vector<std::string>& command_data, int cards_start_index);

    /// @brief Extracts card object from string like ♦3 or ♦A
    /// @param card_str - string to extract card from
    /// @return - created Card object
    utils::Card getCardFromString(const std::string& card_str);

} // namespace command
