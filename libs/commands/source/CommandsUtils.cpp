#include <vector>
#include <string>
#include <commands/CommandsUtils.hpp>
#include <utils/Bid.hpp>
#include <utils/Card.hpp>
#include <utils/Player.hpp>

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
/// BID [ position ] [ trump ] [ deal ]
/// where trump is one from {NO_TRUMP, PASS, SPADES, HEARTS, DIAMONDS, CLUBS}
/// and deal is from 1 to 7
utils::Bid parseBidCommand(std::vector<std::string>& command_data)
{
    utils::Trump trump;
    if(command_data[2] == "PASS")
        trump = utils::Trump::PASS;
    else if(command_data[2] == "NO_TRUMP")
        trump = utils::Trump::NO_TRUMP;
    else if(command_data[2] == "SPADES")
        trump = utils::Trump::SPADES;
    else if(command_data[2] == "HEARTS")
        trump = utils::Trump::HEARTS;
    else if(command_data[2] == "DIAMONDS")
        trump = utils::Trump::DIAMONDS;
    else if(command_data[2] == "CLUBS")
        trump = utils::Trump::CLUBS;

    int deal = std::stoi(command_data[3]);

    return utils::Bid(trump, deal);
}

/// @brief Generates Card object from command_data
/// @param command_data - split command
/// @return Card created from command
/// bid command should have format:
/// PLAY [ position ] [ card ]
/// where card is like: ♦5
utils::Card parsePlayCommand(std::vector<std::string>& command_data)
{
    std::string card_str = command_data[2];

    std::string suit_str = card_str.substr(0, 3);
    std::string rank_str = card_str.substr(3);

    utils::Suit suit;

    if(suit_str == "♣")
        suit = utils::Suit::CLUBS;
    else if(suit_str == "♦")
        suit = utils::Suit::DIAMONDS;
    else if(suit_str == "♥")
        suit = utils::Suit::HEARTS;
    else if(suit_str == "♠")
        suit = utils::Suit::SPADES;

    int rank;
    if(rank_str == "A")
        rank = utils::RoyalRank::ACE;
    else if(rank_str == "K")
        rank = utils::RoyalRank::KING;
    else if(rank_str == "Q")
        rank = utils::RoyalRank::QUEEN;
    else if(rank_str == "J")
        rank = utils::RoyalRank::JACK;
    else
    {
        rank = std::atoi(rank_str.c_str());
    }

    return utils::Card(rank, suit);
}

utils::Position parseSetPosCommand(std::vector<std::string>& command_data)
{
    return utils::Position::NORTH;
}

};
