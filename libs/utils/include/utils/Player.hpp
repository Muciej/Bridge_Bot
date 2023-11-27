#pragma once
#include <vector>
#include <utility>
#include <string>
#include <utils/Card.hpp>

namespace utils
{

enum Position
{
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

Position getPartnerPosition(const Position& pos);

class Player
{
    public:
    std::string name;
    unsigned int score = 0;
    Position position;
    bool is_bot;
    std::vector<utils::Card> hand;

    Player() = default;    
    Player(std::string n, Position pos, bool _is_bot) : name(std::move(n)), position(std::move(pos)), is_bot(_is_bot) {};
};

bool operator==(const Player& lhs, const Player& rhs);

};  // namespace utils
