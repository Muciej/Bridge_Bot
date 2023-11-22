#pragma once
#include <utility>
#include <stdexcept>
#include <string>

namespace Cards
{

enum class Suit
{
    CLUBS = 0,
    DIAMONDS = 1,
    HEARTS = 2,
    SPADES = 3
};

enum RoyalRank
{
    JACK = 11,
    QUEEN = 12,
    KING = 13,
    ACE = 14
};

struct Card
{
    char rank = 2;
    Suit suit = Suit::CLUBS;

    Card() = default;
    Card(const char& r, const Suit& s) : suit(s)
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
};

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

};
