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
    PASS = 5,
};

struct Bid
{
    Trump trump = Trump::PASS;
    int deal = 0;

    Bid() = default;
    Bid(const Trump& _trump, const int& _deal);

};

bool operator==(const Bid& b1, const Bid& b2);
bool operator<(const Bid& b1, const Bid& b2);
bool operator>(const Bid& b1, const Bid& b2);

};
