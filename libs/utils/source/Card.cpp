#include <utils/Card.hpp>
#include <ostream>
#include <stdexcept>
#include <string>

namespace utils
{

Card::Card(const char& r, const Suit& s) : suit(s)
{
    if (r < 2 || r > 14)
    {
        std::string error_msg("Invalid card rank: ", r);
        throw std::range_error(error_msg);
    } else 
    {
        rank = r;
    }
}

std::ostream& operator<<(std::ostream& stream, const Card& card)
{
    switch (card.suit)
    {
        case Suit::CLUBS:
            stream<<"♣";
            break;
        case Suit::DIAMONDS:
            stream<<"♦";
            break;
        case Suit::HEARTS:
            stream<<"♥";
            break;
        case Suit::SPADES:
            stream<<"♠";
            break;
    }
    switch (card.rank)
    {
        case RoyalRank::JACK:
            stream<<"J";
            break;
        case RoyalRank::QUEEN:
            stream<<"Q";
            break;
        case RoyalRank::KING:
            stream<<"K";
            break;
        case RoyalRank::ACE:
            stream<<"A";
            break;
        default:
            stream<<static_cast<int>(card.rank);
            break;
    }
    return stream;
}

bool operator==(const Card& lhs, const Card& rhs)
{
    return lhs.rank == rhs.rank && lhs.suit == rhs.suit;
}

};