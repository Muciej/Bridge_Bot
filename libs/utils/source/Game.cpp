#include <utils/Game.hpp>

namespace utils
{
    Trick Game::getCurentTrick()
    {
        return tricks[current_trick];
    }

}; // namespace utils
