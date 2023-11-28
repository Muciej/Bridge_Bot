#include <utils/Player.hpp>
#include <vector>
#include <algorithm>

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

void Player::drawCard(Card to_draw)
{
    auto newEnd = std::remove(hand.begin(), hand.end(), to_draw);
    hand.erase(newEnd, hand.end());
}

}; // namespace utils
