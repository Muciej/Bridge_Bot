#pragma once
#include <utils/Bid.hpp>
#include <utils/Player.hpp>
#include <vector>

namespace utils
{

using PlayerBid = std::pair<utils::Position, Bid>;

class Bidding
{
    public:
    std::vector<PlayerBid> history;
    
    bool addBid(const utils::Position& pos, const Bid& bid);
    bool isBiddingEnded();
    void clear();

};
    
};
