#pragma once
#include <vector>
#include <utility>
#include "CardsUtils.hpp"

class Player
{
    private:
    std::vector<unsigned char> hand;
    unsigned int score;
    unsigned char const position;

    public:
    Player() = default;
    Player(const unsigned char& position, std::vector<unsigned char> h): hand{std::move(h)}, position{std::move(position)} {};

    bool cardDrawed(const Suit& suit);
    
};