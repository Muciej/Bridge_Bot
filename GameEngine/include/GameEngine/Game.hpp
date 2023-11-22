#pragma once
#include <vector>
#include <iostream>
#include "Player.hpp"

class Game
{
public:
    Game() = default;
private:
    unsigned char bid;
    std::vector<Player> players;
};