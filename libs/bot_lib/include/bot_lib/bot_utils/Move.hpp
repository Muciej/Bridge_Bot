#pragma once
#include "../bot_utils/GameState.hpp"
#include <utils/Card.hpp>
#include <utils/Player.hpp>

namespace bot
{


struct Move
{
    int placed_card;
    utils::Position who_placed_card;
    GameState state_after;

    Move() = default;
    Move(int card) : placed_card(card) {};
    Move(int card, const utils::Position pos, const GameState& state) : placed_card(card), who_placed_card(pos), state_after(state) {};
};


} // namespace bot
