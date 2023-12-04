#pragma once

namespace bot
{

struct GameState
{
    // some form of info about cards and probability of their ownership
    // bots pair tricks won
    // bool in_trick
    // Card highest card played by ohter pair
    bool maximize;
    bool game_end;
};

} // namespace bot
