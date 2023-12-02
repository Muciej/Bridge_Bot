#pragma once
#include <ostream>

namespace utils
{

enum class Suit
{
    CLUBS = 0,
    DIAMONDS = 1,
    HEARTS = 2,
    SPADES = 3,
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
    Card(const char& r, const Suit& s);
};

std::ostream& operator<<(std::ostream& stream, const Card& card);
bool operator==(const Card& lhs, const Card& rhs);
bool operator<(const Card& lhs, const Card& rhs);

};
