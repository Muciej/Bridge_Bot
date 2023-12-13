#include <vector>
#include <string>
#include <stdexcept>
#include <commands/CommandsUtils.hpp>
#include <utils/Bid.hpp>
#include <utils/Card.hpp>
#include <utils/Player.hpp>

namespace commands
{

utils::Position getPositionFromString(const std::string& pos_string)
{
    utils::Position pos;
    if(pos_string == "NORTH")
        pos = utils::Position::NORTH;
    else if(pos_string == "SOUTH")
        pos = utils::Position::SOUTH;
    else if(pos_string == "EAST")
        pos = utils::Position::EAST;
    else if(pos_string == "WEST")
        pos = utils::Position::WEST;
    else
        throw std::runtime_error("Illegal position!");
    return pos;
}

std::string parseCommand(const std::string& command, std::vector<std::string>& command_data)
{
    auto command_cpy = command;
    command_data.clear();
    size_t pos;

    while ((pos = command_cpy.find(' ')) != std::string::npos) {
        command_data.push_back(command_cpy.substr(0, pos));
        command_cpy.erase(0, pos + 1);
    }
    if (command_cpy.length() > 0)
    {
        command_data.push_back(command_cpy);
    }

    return command_data.at(0);
}

utils::Bid parseBidCommand(const std::vector<std::string>& command_data)
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

utils::Card parsePlayCommand(const std::vector<std::string>& command_data)
{
    return getCardFromString(command_data[2]);
}

utils::Position parseSetPosCommand(const std::vector<std::string>& command_data)
{
    return commands::getPositionFromString(command_data[2]);
}

std::vector<utils::Card> parseHandCommand(const std::vector<std::string>& command_data, int cards_start_index)
{
    std::vector<utils::Card> hand;

    auto iterator = command_data.begin() + cards_start_index;
    for(; iterator != command_data.end(); iterator++)
    {
        hand.push_back(getCardFromString(*iterator));
    }

    return hand;
}

utils::Card getCardFromString(const std::string& card_str)
{
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

};
