#include <sstream>
#include <algorithm>
#include <utils/Printer.hpp>
#include <utils/Card.hpp>

namespace printer
{

std::string printHand(const std::vector<utils::Card>& hand)
{
    std::stringstream ss;
    for(const auto& card : hand)
    {
        ss << card << " ";
    }
    return ss.str();
}

std::string printSortedHand(std::vector<utils::Card> hand)
{
    std::sort(hand.begin(), hand.end());
    return printHand(hand);
}

std::string printPosition(const utils::Position& pos)
{
    switch (pos)
    {
    case utils::Position::NORTH:
        return "NORTH";
    case utils::Position::SOUTH:
        return "SOUTH";
    case utils::Position::EAST:
        return "EAST";
    case utils::Position::WEST:
        return "WEST";
    default:
        return "";
    }
}

std::string printSuit(const utils::Suit& suit)
{
    switch (suit)
    {
    case utils::Suit::SPADES :
        return "SPADES";
    case utils::Suit::HEARTS :
        return "HEARTS";
    case utils::Suit::DIAMONDS :
        return "DIAMONDS";
    case utils::Suit::CLUBS :
        return "CLUBS";
    default:
        return "";
    }
}

} // namespace printer
