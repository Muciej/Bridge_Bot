#include <bot_lib/bid_evaluator/BaseBidEvaluator.hpp>
#include <utils/Player.hpp>

namespace bot
{

utils::Bid BaseBidEvaluator::evalueNextBid(GameState& state, const GlobalGameState& globalState)
{
    int legal_samples_count = 0;
    for(int i = 0; i<4; i++)
    {
        resetPoints(state, static_cast<utils::Position>(i));
    }

    while(legal_samples_count < REQUIRED_LEGAL_SAMPLES)
    {

    }

    return utils::Bid();
}

} // namespace bot
