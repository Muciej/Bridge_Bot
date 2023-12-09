#include <bot_lib/state_evaluator/BaseEvaluator.hpp>

namespace bot
{

int BaseEvaluator::evaluateState(const GameState& state, const GlobalGameState& global_state)
{
    int evaluation = 40 * state.pair_tricks_won;
    for(int i = 0; i<4; i++)
    {
        int multiplier = i == static_cast<int>(global_state.bot_position) ? ALLY_POINT_MULTIPLIER : ENEMY_POINT_MULTIPLIER;
        for(int j = 0; j<=39; j+=13)
        {
            evaluation += multiplier * state.player_cards_points[i][j+9];
            evaluation += multiplier * 2 * state.player_cards_points[i][j+10];
            evaluation += multiplier * 3 * state.player_cards_points[i][j+11];
            evaluation += multiplier * 4 * state.player_cards_points[i][j+12];
        }
    }
    return evaluation;
}

} // namespace bot
