#pragma once
#include <map>
#include <utils/Player.hpp>
#include <utils/Bid.hpp>
#include "../bot_utils/GameState.hpp"
#include "../bot_utils/GlobalGameState.hpp"

namespace bot
{

using utils::Bid;
using utils::Trump;

const int REQUIRED_LEGAL_SAMPLES = 100;

/// @brief Data structure used to store information
/// about cards
struct BiddingParams
{
    char all_points = 0;
    char spades_points = 0;
    char spades_cards = 0;
    char hearts_points = 0;
    char hearts_cards = 0;
    char diamonds_points = 0;
    char diamonds_cards = 0;
    char clubs_points = 0;
    char clubs_cards = 0;
};

bool operator<(const BiddingParams& b1, const BiddingParams& b2);

struct ContractRequirements
{
    char all_points_min = 0;
    char colour_points_min = 0;
    char colour_length_min = 0;

    ContractRequirements() = default;
    ContractRequirements(char all_p, char col_p, char col_l) : all_points_min(all_p), colour_points_min(col_p), colour_length_min(col_l) {};
};

const std::map<utils::Bid, ContractRequirements> conract_reuiremets_map{
    {Bid(Trump::NO_TRUMP, 1), ContractRequirements{20, 0, 0}},
    {Bid(Trump::NO_TRUMP, 2), ContractRequirements{23, 0, 0}},
    {Bid(Trump::NO_TRUMP, 3), ContractRequirements{26, 0, 0}},
    {Bid(Trump::NO_TRUMP, 4), ContractRequirements{28, 0, 0}},
    {Bid(Trump::NO_TRUMP, 5), ContractRequirements{30, 0, 0}},
    {Bid(Trump::NO_TRUMP, 6), ContractRequirements{32, 0, 0}},
    {Bid(Trump::NO_TRUMP, 7), ContractRequirements{36, 0, 0}},

    {Bid(Trump::CLUBS, 1), ContractRequirements{16, 4, 6}},
    {Bid(Trump::CLUBS, 2), ContractRequirements{21, 5, 7}},
    {Bid(Trump::CLUBS, 3), ContractRequirements{23, 6, 8}},
    {Bid(Trump::CLUBS, 4), ContractRequirements{26, 7, 9}},
    {Bid(Trump::CLUBS, 5), ContractRequirements{29, 8, 10}},
    {Bid(Trump::CLUBS, 6), ContractRequirements{30, 9, 11}},
    {Bid(Trump::CLUBS, 7), ContractRequirements{31, 10, 12}},

    {Bid(Trump::DIAMONDS, 1), ContractRequirements{16, 4, 6}},
    {Bid(Trump::DIAMONDS, 2), ContractRequirements{21, 5, 7}},
    {Bid(Trump::DIAMONDS, 3), ContractRequirements{23, 6, 8}},
    {Bid(Trump::DIAMONDS, 4), ContractRequirements{26, 7, 9}},
    {Bid(Trump::DIAMONDS, 5), ContractRequirements{29, 8, 10}},
    {Bid(Trump::DIAMONDS, 6), ContractRequirements{30, 9, 11}},
    {Bid(Trump::DIAMONDS, 7), ContractRequirements{31, 10, 12}},

    {Bid(Trump::HEARTS, 1), ContractRequirements{16, 4, 6}},
    {Bid(Trump::HEARTS, 2), ContractRequirements{21, 5, 7}},
    {Bid(Trump::HEARTS, 3), ContractRequirements{23, 6, 8}},
    {Bid(Trump::HEARTS, 4), ContractRequirements{26, 7, 9}},
    {Bid(Trump::HEARTS, 5), ContractRequirements{29, 8, 10}},
    {Bid(Trump::HEARTS, 6), ContractRequirements{30, 9, 11}},
    {Bid(Trump::HEARTS, 7), ContractRequirements{31, 10, 12}},

    {Bid(Trump::SPADES, 1), ContractRequirements{16, 4, 6}},
    {Bid(Trump::SPADES, 2), ContractRequirements{21, 5, 7}},
    {Bid(Trump::SPADES, 3), ContractRequirements{23, 6, 8}},
    {Bid(Trump::SPADES, 4), ContractRequirements{26, 7, 9}},
    {Bid(Trump::SPADES, 5), ContractRequirements{29, 8, 10}},
    {Bid(Trump::SPADES, 6), ContractRequirements{30, 9, 11}},
    {Bid(Trump::SPADES, 7), ContractRequirements{31, 10, 12}}
};

class BidEvaluator
{
    public:
    virtual utils::Bid evalueNextBid(const GameState& state, const GlobalGameState& globalState) = 0;
    virtual void updateAfterPlacedBid(GameState& state, const GlobalGameState& global_state) = 0;
};


} // namespace bot
