#pragma once
#include "../bot_utils/GameState.hpp"
#include <utils/Card.hpp>

namespace bot
{


struct Move
{
    utils::Card placed_card;
    GameState state_after;
    int evaluation;
};


} // namespace bot
