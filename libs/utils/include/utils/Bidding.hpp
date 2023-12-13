#pragma once
#include <vector>
#include <optional>
#include <utils/Bid.hpp>
#include <utils/Player.hpp>

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

    /// @brief Returns declarer - that is player from winner pair, 
    /// who first proposed the trump
    /// @return position of declarer
    std::optional<Position> getDeclarer();

    /// @brief Returns contract established during bidding
    std::optional<Bid> getContract();
};

};
