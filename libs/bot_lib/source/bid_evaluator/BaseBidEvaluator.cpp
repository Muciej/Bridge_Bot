#include <bot_lib/bid_evaluator/BaseBidEvaluator.hpp>
#include <utils/Player.hpp>
#include <utils/Card.hpp>
#include <utils/CardsUtils.hpp>

namespace bot
{

utils::Bid BaseBidEvaluator::evalueNextBid(const GameState& state, const GlobalGameState& globalState)
{
    auto ally_params = estimateParams(state, globalState.bot_position);
    return getBidFromTable(ally_params);
}

void BaseBidEvaluator::updateAfterPlacedBid(GameState& state, const GlobalGameState& global_state)
{
    if( global_state.now_moving == global_state.bot_position)
    {
        return;
    }

    const auto& placed_bid = global_state.bidding.back();
    if (placed_bid.trump == utils::Trump::PASS) // pass does not provide any new information
        return;

    BiddingParams north_pair;
    BiddingParams west_pair;
    if(global_state.now_moving == utils::Position::NORTH || global_state.now_moving == utils::Position::SOUTH)
    {
        north_pair = getEstimatedParamsFromContractRequirements(getRequirementsForBid(placed_bid), placed_bid.trump);
        west_pair = estimateParams(state, utils::Position::WEST);
    } else
    {
        north_pair = estimateParams(state, utils::Position::NORTH);
        west_pair = getEstimatedParamsFromContractRequirements(getRequirementsForBid(placed_bid), placed_bid.trump);
    }

    for(int i = 0; i<4; i++)
    {
        if(i != static_cast<int>(global_state.bot_position))
            resetPoints(state, static_cast<utils::Position>(i));
    }

    std::vector<int> bot_cards;
    bot_cards.reserve(13);
    for(int i = 0; i<52; i++)
    {
        if( state.player_cards_points[static_cast<int>(global_state.bot_position)][i] > 0)
        {
            bot_cards.push_back(i);
        }
    }

    int legal_samples = 0;
    while(legal_samples < REQUIRED_LEGAL_SAMPLES)
    {
        std::vector<int> deal;
        dealer.dealCardsIntoIntTable(deal, bot_cards);
        dealer.shuffleDeck();
        if (checkDealWithEstimate(deal, bot_cards, north_pair, west_pair, global_state.bot_position))
        {
            giveCardsPoints(deal, state, global_state.bot_position);
            legal_samples++;
        }
    }
}

void estimatePoints(float cards_prob_1[52], float cards_prob_2[52], BiddingParams& params)
{
    float color_points[]{0.0, 0.0, 0.0, 0.0};
    for(int i = 0; i < 4; i++)
    {
        color_points[i] += cards_prob_1[(13 * i) + 9] + cards_prob_2[(13 * i) + 9];              // JACK
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

bool compareRequirementWithParams(const BiddingParams& params, const ContractRequirements& requirement , const utils::Trump trump)
{
    bool requirements_satisfied = true;
    if ( params.all_points < requirement.all_points_min)
        requirements_satisfied = false;

    if (trump != utils::Trump::NO_TRUMP)
    {
        char color_length;
        char color_points;
        switch (trump)
        {
        case utils::Trump::CLUBS :
            color_length = params.clubs_cards;
            color_points = params.clubs_points;
            break;
        case utils::Trump::DIAMONDS :
            color_length = params.diamonds_cards;
            color_points = params.diamonds_points;
            break;
        case utils::Trump::HEARTS :
            color_length = params.hearts_cards;
            color_points = params.hearts_points;
            break;
        case utils::Trump::SPADES :
            color_length = params.spades_cards;
            color_points = params.spades_points;
            break;
        default:
            break;
        }
        if (color_length < requirement.colour_length_min || color_points < requirement.colour_points_min)
            requirements_satisfied = false;
    }
    return requirements_satisfied;
}

utils::Bid BaseBidEvaluator::getBidFromTable(const BiddingParams& params)
{
    Bid bid;
    for(const auto& pair : conract_reuiremets_map)
    {
        if(compareRequirementWithParams(params, pair.second, pair.first.trump))
            bid = pair.first;
        else
            break;
    }
    return bid;
}

ContractRequirements BaseBidEvaluator::getRequirementsForBid(const utils::Bid& bid)
{
    return conract_reuiremets_map.find(bid)->second;
}

BiddingParams BaseBidEvaluator::getEstimatedParamsFromContractRequirements(const ContractRequirements& requirements, const utils::Trump& trump)
{
    BiddingParams params;
    switch (trump)
    {
    case utils::Trump::CLUBS :
        params.clubs_cards = requirements.colour_length_min;
        params.clubs_points = requirements.colour_points_min;
        break;
    case utils::Trump::DIAMONDS :
        params.diamonds_cards = requirements.colour_length_min;
        params.diamonds_points = requirements.colour_points_min;
        break;
    case utils::Trump::HEARTS :
        params.hearts_cards = requirements.colour_length_min;
        params.hearts_points = requirements.colour_points_min;
        break;
    case utils::Trump::SPADES :
        params.spades_cards = requirements.colour_length_min;
        params.spades_points = requirements.colour_points_min;
        break;
    default:
        break;
    }
    params.all_points = requirements.all_points_min;
    return params;
}

void getParamsFromDealDetails(const std::vector<int>& card_table, int start_ind, BiddingParams& current)
{
    utils::Card c;
    for(int j = 0; j < 13; j++)
    {
        c = utils::getCardFromInt(card_table[start_ind + j]);
        switch (c.suit)
        {
        case utils::Suit::CLUBS:
            current.clubs_points += std::max(c.rank-10, 0);
            current.clubs_cards++;
            break;
        case utils::Suit::DIAMONDS:
            current.diamonds_points += std::max(c.rank-10, 0);
            current.diamonds_cards++;
            break;
        case utils::Suit::HEARTS:
            current.hearts_points += std::max(c.rank-10, 0);
            current.hearts_cards++;
            break;
        case utils::Suit::SPADES:
            current.spades_points += std::max(c.rank-10, 0);
            current.spades_cards++;
            break;
        default:
            break;
        }
        current.all_points += std::max(c.rank-10, 0);
    }
}

std::pair<BiddingParams, BiddingParams> BaseBidEvaluator::getParamsFromDeal(const std::vector<int>& deal, const std::vector<int>& bot_cards, const utils::Position& bot_position)
{
    BiddingParams north_pair, west_pair;
    auto position = utils::getNextPosition(bot_position);
    for(int i = 0; i<3; i++)
    {
        BiddingParams& current = static_cast<int>(position)%2 == 0 ? north_pair : west_pair;
        getParamsFromDealDetails(deal, i*13, current);
        position = utils::getNextPosition(position);
    }
    BiddingParams& current = static_cast<int>(bot_position)%2 == 0 ? north_pair : west_pair;
    getParamsFromDealDetails(bot_cards, 0, current);
    return {north_pair, west_pair};
}

bool BaseBidEvaluator::checkDealWithEstimate(const std::vector<int>& deal, const std::vector<int>& bot_cards, const BiddingParams& pairNorth, const BiddingParams& pairWest, const utils::Position& bot_position)
{
    auto params_pair = getParamsFromDeal(deal, bot_cards, bot_position);
    return pairNorth < params_pair.first  &&  pairWest < params_pair.second;
}

void BaseBidEvaluator::giveCardsPoints(const std::vector<int>& deal, GameState& state, const utils::Position& bot_position)
{
    auto position = utils::getNextPosition(bot_position);
    for(int i = 0; i<3; i++)
    {
        for(int j = 0; j<13; j++)
        {
            state.player_cards_points[static_cast<int>(position)][deal[(i * 13) + j]]++;
        }
        position = utils::getNextPosition(position);
    }
}

bool operator<(const BiddingParams& b1, const BiddingParams& b2)
{
    bool is_ok = true;
    if( b1.all_points >= b2.all_points) is_ok = false;
    if( b1.clubs_cards >= b2.clubs_cards) is_ok = false;
    if( b1.clubs_points >= b2.clubs_points) is_ok = false;
    if( b1.diamonds_cards >= b2.diamonds_cards) is_ok = false;
    if( b1.diamonds_points >= b2.diamonds_points) is_ok = false;
    if( b1.hearts_cards >= b2.hearts_cards) is_ok = false;
    if( b1.hearts_points >= b2.hearts_points) is_ok = false;
    if( b1.spades_cards >= b2.spades_cards) is_ok = false;
    if( b1.spades_points >= b2.spades_points) is_ok = false;
    return is_ok;
}

} // namespace bot
