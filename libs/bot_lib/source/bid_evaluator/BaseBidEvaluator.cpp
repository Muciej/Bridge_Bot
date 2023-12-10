#include <bot_lib/bid_evaluator/BaseBidEvaluator.hpp>
#include <utils/Player.hpp>

namespace bot
{

utils::Bid BaseBidEvaluator::evalueNextBid(const GameState& state, const GlobalGameState& globalState)
{
    auto ally_params = estimateParams(state, globalState.bot_position);
    return getBidFromTable(ally_params, globalState.bot_position);
}

void BaseBidEvaluator::updateAfterPlacedBid(GameState& state, const GlobalGameState& global_state)
{
    if( state.now_moving == global_state.bot_position)
    {
        return;
    }

    const auto& placed_bid = *global_state.bidding.end();
    BiddingParams north_pair;
    BiddingParams west_pair;
    if(state.now_moving == utils::Position::NORTH || state.now_moving == utils::Position::NORTH)
    {
        north_pair = getEstimatedParamsFromContractRequirements(getRequirementsForBid(placed_bid));
        west_pair = estimateParams(state, utils::Position::WEST);
    } else
    {
        north_pair = estimateParams(state, utils::Position::NORTH);
        west_pair = getEstimatedParamsFromContractRequirements(getRequirementsForBid(placed_bid));
    }

    for(int i = 0; i<4; i++)
    {
        resetPoints(state, static_cast<utils::Position>(i));
    }

    int legal_samples = 0;
    while(legal_samples < REQUIRED_LEGAL_SAMPLES)
    {
        // dealer generate deals
        std::vector<int> deal;
        if (checkDealWithEstimate(deal, north_pair, west_pair))
        {
            giveCardsPoints(deal, state);
            legal_samples++;
        }
    }
}

void estimatePoints(float cards_prob_1[52], float cards_prob_2[52], BiddingParams& params)
{
    float color_points[]{0.0, 0.0, 0.0, 0.0};
    for(int i = 0; i < 4; i++)
    {
        color_points[i] += cards_prob_1[(13 * i) + 9] + cards_prob_2[(13 * i) + 9];      // JACK
        color_points[i] += 2.0 * (cards_prob_1[(13 * i) + 10] + cards_prob_2[(13 * i) + 10]);    // QUEEN
        color_points[i] += 3.0 * (cards_prob_1[(13 * i) + 11] + cards_prob_2[(13 * i) + 11]);    // KING
        color_points[i] += 4.0 * (cards_prob_1[(13 * i) + 12] + cards_prob_2[(13 * i) + 12]);    // ACE
    }
    params.clubs_points = static_cast<char>(color_points[0]);
    params.diamonds_points = static_cast<char>(color_points[1]);
    params.hearts_points = static_cast<char>(color_points[2]);
    params.spades_points = static_cast<char>(color_points[3]);
    params.all_points = static_cast<char>(color_points[0] + color_points[1] + color_points[2] + color_points[3]);
}

void estimateLength(float cards_prob_1[52], float cards_prob_2[52], BiddingParams& params)
{
    float color_length[]{0.0, 0.0, 0.0, 0.0};
    for(int i = 0; i < 13; i++)
    {
        color_length[0] += cards_prob_1[i] + cards_prob_2[i];      // JACK
        color_length[1] += cards_prob_1[13 + i] + cards_prob_2[13 + i];    // QUEEN
        color_length[2] += cards_prob_1[26 + i] + cards_prob_2[26 + i];    // KING
        color_length[3] += cards_prob_1[39 + i] + cards_prob_2[39 + i];    // ACE
    }
    params.clubs_cards = static_cast<char>(color_length[0]);
    params.diamonds_cards = static_cast<char>(color_length[1]);
    params.hearts_cards = static_cast<char>(color_length[2]);
    params.spades_cards = static_cast<char>(color_length[3]);
}

BiddingParams BaseBidEvaluator::estimateParams(const GameState& state, const utils::Position& position)
{
    BiddingParams params;
    float cards_prob_1[52];
    float cards_prob_2[52];
    if( position == utils::Position::NORTH || position == utils::Position::SOUTH)
    {
        getCardProbability(state, cards_prob_1, utils::Position::NORTH);
        getCardProbability(state, cards_prob_2, utils::Position::SOUTH);
    } else
    {
        getCardProbability(state, cards_prob_1, utils::Position::WEST);
        getCardProbability(state, cards_prob_2, utils::Position::EAST);
    }
    estimatePoints(cards_prob_1, cards_prob_2, params);
    estimateLength(cards_prob_1, cards_prob_2, params);
    return params;
}


utils::Bid BaseBidEvaluator::getBidFromTable(const BiddingParams& params, const utils::Position& position)
{
    return Bid();
}

ContractRequirements BaseBidEvaluator::getRequirementsForBid(const utils::Bid& bid)
{
    return ContractRequirements();
}

BiddingParams BaseBidEvaluator::getEstimatedParamsFromContractRequirements(const ContractRequirements& requirements)
{
    return BiddingParams();
}

std::pair<BiddingParams, BiddingParams> BaseBidEvaluator::getParamsFromDeal(const std::vector<int> deal)
{
    return std::pair<BiddingParams, BiddingParams>();
}

bool BaseBidEvaluator::checkDealWithEstimate(const std::vector<int> deal, const BiddingParams& pairNorth, const BiddingParams& pairWest)
{
    return true;
}

void BaseBidEvaluator::giveCardsPoints(const std::vector<int> deal, GameState& state)
{

}


} // namespace bot
