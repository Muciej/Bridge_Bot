#include <bot_lib/bot_utils/GameState.hpp>
#include <bot_lib/bid_evaluator/BidEvaluator.hpp>

namespace bot
{

void resetPoints(GameState& state, utils::Position position)
{
    for(int i = 0; i<52; i++)
    {
        state.player_cards_points[static_cast<int>(position)][i] = 0;
    }
}

void getCardProbability(const GameState& state, float cards_prob[52], utils::Position position)
{
    for(int i = 0; i<52; i++){
        cards_prob[i] = static_cast<float>(state.player_cards_points[static_cast<int>(position)][i]) / static_cast<float>(REQUIRED_LEGAL_SAMPLES);
    }
}

} // namespace bot
