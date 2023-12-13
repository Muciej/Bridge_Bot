#pragma once
#include <utils/Card.hpp>
#include <utils/Player.hpp>

namespace bot
{

/// @brief Class used to store data about game state
/// it stores data that can change within move or bid
struct GameState
{
    utils::Position tricker;
    utils::Position placed_high_card;
    utils::Suit trick_suit;
    int high_card;
    int player_cards_points[4][52];
    char pair_tricks_won = 0;
    char current_trick_no = 1;
    bool in_trick = false;
    bool maximize;
    bool game_end = false;
};

void resetPoints(GameState& state, utils::Position position);
void getCardProbability(const GameState& state, float cards_prob[52], utils::Position position);

} // namespace bot
