#include <utils/Player.hpp>
#include <utils/CardsUtils.hpp>

namespace utils
{

bool operator==(const Player& lhs, const Player& rhs)
{
    return lhs.name == rhs.name && lhs.position == rhs.position && lhs.is_bot == rhs.is_bot;
}

Position getPartnerPosition(const Position& pos)
{
    return static_cast<Position>((static_cast<int>(pos) + 2)%4);
}

std::pair<Position, Position> getEnemiesPositions(const Position& pos)
{
    auto pos1 = static_cast<Position>((static_cast<int>(pos) + 1)%4);
    auto pos2 = static_cast<Position>((static_cast<int>(pos) + 3)%4);
    return std::pair(pos1, pos2);
}

Position getPrevPosition(const Position& pos)
{
    return static_cast<Position>((static_cast<int>(pos) + 3)%4);
}

Position getNextPosition(const Position& pos)
{
    return static_cast<Position>((static_cast<int>(pos) + 1)%4);
}

void Player::drawCard(Card to_draw)
{
    utils::drawCardFromHand(hand, to_draw);
}

}; // namespace utils
