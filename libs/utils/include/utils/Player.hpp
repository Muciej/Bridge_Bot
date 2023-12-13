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

/// @brief Returns position of player's partner
/// @param pos - player position
Position getPartnerPosition(const Position& pos);

/// @brief Returns std::pair containing position of enemies
/// @param pos - position of player whom enemies we want
std::pair<Position, Position> getEnemiesPositions(const Position& pos);

/// @brief Returns previous position (counter-clockwise)
Position getPrevPosition(const Position& pos);

/// @brief Returns next position clockwise
Position getNextPosition(const Position& pos);

/// @brief Object used to store informations about player
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

    void drawCard(Card to_draw);
};

bool operator==(const Player& lhs, const Player& rhs);

};  // namespace utils
