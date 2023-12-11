#include <gtest/gtest.h>
#include <bot_lib/bot_utils/GlobalGameState.hpp>
#include <bot_lib/bot_utils/GameState.hpp>
#include <bot_lib/state_evaluator/BaseEvaluator.hpp>
#include <utils/Player.hpp>
#include <bot_lib/bid_evaluator/BidEvaluator.hpp>

using bot::GameState;
using bot::GlobalGameState;

namespace
{

const int m = bot::REQUIRED_LEGAL_SAMPLES;

const int card_points_table[4][52]{
    // CLUBS                                 // DIAMONDS                             // HEARTS                               // SPADES
    {0, m, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  m, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, m, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, m, m, 0, 0, m, 0, 0, 0, 0},  // NORTH
    {0, 0, 20,0, 0, 0, 15,0, 0, 15,0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 70,0, 0, 0, 0,  0, 0, 0, 0, 70,0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // EAST
    {m, 0, 0, m, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, m, 0, 0, 0, m, 0, 0, 0, 0, 0,  0, m, 0, 0, 0, 0, 0, 0, 0, 0, m, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // SOUTH
    {0, 0, 10,0, 0, 0, 0, 30,0, 0, 0, 0, 45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 50,0, 0, 0, 60,0, 0}   // WEST
};

GameState getExampleGameState()
{
    GameState state;
    state.current_trick_no = 7;
    state.pair_tricks_won = 4;
    state.game_end = false;
    for(int i = 0; i<4 ; i++)
    {
        for(int j = 0; j<52; j++)
        {
            state.player_cards_points[i][j] = card_points_table[i][j];
        }
    }
    return state;
}

GlobalGameState getExampleGlobalGameState()
{
    GlobalGameState global_state;
    global_state.bot_position = utils::Position::NORTH;
    global_state.bot_partner_posititon = utils::Position::SOUTH;
    global_state.bot_name = "Bot";
    return global_state;
}

} // namespace

TEST(StateEvaluatorTests, EvaluateStateTest)
{
    auto state = getExampleGameState();
    auto globalState = getExampleGlobalGameState();

    bot::BaseEvaluator evaluator;
    EXPECT_EQ(evaluator.evaluateState(state, globalState), 160 - 3 - 2 - 2);
}
