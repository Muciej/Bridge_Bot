#include <bot_lib/bot_utils/Move.hpp>

namespace bot
{

bool operator==(const Move& lhs, const Move& rhs)
{
    return lhs.placed_card == rhs.placed_card;
}

} // namespace bot
