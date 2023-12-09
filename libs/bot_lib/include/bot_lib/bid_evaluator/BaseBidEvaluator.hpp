#pragma once
#include <utils/Player.hpp>
#include "BidEvaluator.hpp"
#include "../bot_utils/GameState.hpp"
#include "../bot_utils/GlobalGameState.hpp"

namespace bot
{

class BaseBidEvaluator : public BidEvaluator
{
    public:
    utils::Bid evalueNextBid(const GameState& state, const GlobalGameState& globalState) override;
};


} // namespace bot
