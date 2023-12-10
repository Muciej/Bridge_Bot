#include <bot_lib/bot_utils/GameState.hpp>

namespace bot
{

void resetPoints(GameState& state, utils::Position position)
{
    for(int i = 0; i<52; i++)
    {
        state.player_cards_points[static_cast<int>(position)][i] = 0;
    }
    state.player_cards_points_sum[static_cast<int>(position)] = 0;
}

void getCardProbability(const GameState& state, float cards_prob[52], utils::Position position)
{
    // TODO
}

} // namespace bot
