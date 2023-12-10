#pragma once
#include "../bot_utils/GameState.hpp"
#include <utils/Card.hpp>
#include <utils/Player.hpp>

namespace bot
{


struct Move
{
    int placed_card;
    GameState state_after;

    Move() = default;
    Move(int card) : placed_card(card) {};
};


} // namespace bot
