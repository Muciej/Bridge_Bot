#include <bot_lib/state_evaluator/BaseEvaluator.hpp>

namespace bot
{

int BaseEvaluator::evaluateState(const GameState& state, const GlobalGameState& global_state)
{
    int evaluation = 40 * state.pair_tricks_won;
    for(int i = 0; i<4; i++)
    {
        int multiplier = i == static_cast<int>(global_state.bot_position) ? ALLY_POINT_MULTIPLIER : ENEMY_POINT_MULTIPLIER;
        float cards_prob[52];
        getCardProbability(state, cards_prob, static_cast<utils::Position>(i));
        for(int j = 0; j<=39; j+=13)
        {
            evaluation += multiplier * static_cast<int>(cards_prob[j+9]);
            evaluation += multiplier * static_cast<int>(2.0 * cards_prob[j+10]);
            evaluation += multiplier * static_cast<int>(3.0 * cards_prob[j+11]);
            evaluation += multiplier * static_cast<int>(4.0 * cards_prob[j+12]);
        }
    }
    return evaluation;
}

} // namespace bot
