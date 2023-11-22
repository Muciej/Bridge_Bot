#pragma once
#include <vector>
#include <utility>

class Player
{
    private:
    std::vector<unsigned char> hand;
    unsigned int score;
    unsigned char const position;

    public:
    Player() = default;    
};