#pragma once
#include <stdexcept>

namespace utils
{

enum class Trump
{
    CLUBS = 0,
    DIAMONDS = 1,
    HEARTS = 2,
    SPADES = 3,
    NO_TRUMP = 4,
};

struct Bid
{
    Trump trump;
    int deal;

    Bid() = default;
    Bid(const Trump& s, const int& d);

};

bool operator==(const Bid& b1, const Bid& b2);
bool operator<(const Bid& b1, const Bid& b2);
bool operator>(const Bid& b1, const Bid& b2);

};
