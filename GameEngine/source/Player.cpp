#include <GameEngine/Player.hpp>

namespace Game
{

bool operator==(const Player& lhs, const Player& rhs)
{
    return lhs.name == rhs.name && lhs.position == rhs.position && lhs.is_bot == rhs.is_bot;
}

}; // namespace Game
