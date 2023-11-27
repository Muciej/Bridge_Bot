#pragma once
#include <utils/Bid.hpp>
#include <utils/Player.hpp>
#include <vector>
#include <optional>

namespace utils
{

class Bidding
{
    private:
    std::optional<int> highest_bid_index;
    bool isBidLegal(const Bid& bid);
    int getPassesStrike();
    Position probable_declarer;

    public:
    std::vector<Bid> history;
    
    bool addBid(const Position& pos, const Bid& bid);
    bool isBiddingEnded();
    void clear();
    std::optional<Position> getDeclarer();
    std::optional<Bid> getContract();
};
    
};
