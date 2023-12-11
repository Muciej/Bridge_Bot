#pragma once
#include <vector>
#include <utils/Player.hpp>
#include <utils/Bid.hpp>
#include <utils/Dealer.hpp>
#include "BidEvaluator.hpp"
#include "../bot_utils/GameState.hpp"
#include "../bot_utils/GlobalGameState.hpp"

namespace bot
{

class BaseBidEvaluator : public BidEvaluator
{
    private:
    utils::Dealer dealer;

    BiddingParams estimateParams(const GameState& state, const utils::Position& position);
    utils::Bid getBidFromTable(const BiddingParams& params);
    ContractRequirements getRequirementsForBid(const utils::Bid& bid);
    BiddingParams getEstimatedParamsFromContractRequirements(const ContractRequirements& requirements, const utils::Trump& trump);
    std::pair<BiddingParams, BiddingParams> getParamsFromDeal(const std::vector<int>& deal, const std::vector<int>& bot_cards, const utils::Position& bot_position);
    bool checkDealWithEstimate(const std::vector<int>& deal, const BiddingParams& pairNorth, const BiddingParams& pairWest);
    void giveCardsPoints(const std::vector<int>& deal, GameState& state, const utils::Position& bot_position);

    public:
    utils::Bid evalueNextBid(const GameState& state, const GlobalGameState& globalState) override;
    void updateAfterPlacedBid(GameState& state, const GlobalGameState& global_state) override;

};


} // namespace bot
