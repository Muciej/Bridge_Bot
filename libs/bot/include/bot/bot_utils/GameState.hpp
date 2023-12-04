#pragma once
#include <utils/Player.hpp>
#include <utils/Bid.hpp>

namespace bot
{

struct GameState
{
    // some form of info about cards and probability of their ownership
    // bots pair tricks won
    // bool in_trick
    // Card highest card played by ohter pair
    utils::Position declarer_pos;
    utils::Bid contract;
    bool maximize;
    bool game_end;
};

} // namespace bot
