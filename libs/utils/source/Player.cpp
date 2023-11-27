#include <utils/Player.hpp>

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

}; // namespace utils
