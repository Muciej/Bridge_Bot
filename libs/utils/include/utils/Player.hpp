#pragma once
#include <vector>
#include <utility>
#include <string>

namespace utils
{

enum Position
{
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

class Player
{
    private:
    std::string name;
    unsigned int score = 0;
    Position position;
    bool is_bot;

    public:
    Player() = default;    
    Player(std::string n, Position pos, bool _is_bot) : name(std::move(n)), position(std::move(pos)), is_bot(_is_bot) {};

    friend bool operator==(const Player& lhs, const Player& rhs);
};

bool operator==(const Player& lhs, const Player& rhs);

};  // namespace utils
