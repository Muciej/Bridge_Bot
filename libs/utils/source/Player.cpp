#include <utils/Player.hpp>

namespace utils
{

bool operator==(const Player& lhs, const Player& rhs)
{
    return lhs.name == rhs.name && lhs.position == rhs.position && lhs.is_bot == rhs.is_bot;
}

}; // namespace utils
