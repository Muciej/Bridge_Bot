#pragma once
#include <vector>
#include <iostream>
#include "CardsUtils.hpp"
#include "Player.hpp"

class Game
{
public:
    Game() = default;
private:
    unsigned char bid;
    Suit trump;
    std::vector<Player> players;
};