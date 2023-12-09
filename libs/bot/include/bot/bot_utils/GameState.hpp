#pragma once
#include <utils/Card.hpp>

namespace bot
{

struct GameState
{
    utils::Card card_played_by_opponents;
    unsigned int player_cards_points[4][52];
    unsigned int player_cards_points_sum[4];
    char pair_tricks_won = 0;
    char current_trick_no = 1;
    bool in_trick = false;
    bool maximize;
    bool game_end = false;
};

} // namespace bot
