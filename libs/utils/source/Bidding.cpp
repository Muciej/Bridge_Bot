#include <utils/Bidding.hpp>
#include <optional>

namespace utils
{

int Bidding::getPassesStrike()
{
    int passes_strike = 0;
    auto it = history.end();
    it--;   //now iterator should point to the last element
    while(it != history.begin()-1 && it->trump == utils::Trump::PASS)
    {
        it--;
        passes_strike++;
    }
    return passes_strike;
}

bool Bidding::addBid(const utils::Position& pos, const Bid& bid)
{
    if (isBidLegal(bid))
    {
        history.push_back(bid);
        if(bid.trump != utils::Trump::PASS)
        {
            highest_bid_index = history.size() - 1;
            probable_declarer = pos;
        }

        return true;
    } else 
    {
        return false;
    }
}

bool Bidding::isBiddingEnded()
{
    auto passes_strike = getPassesStrike();
    if(history.size() < 4)
    {
        return false;
    } else 
    {
        return passes_strike >= 3;
    }

}

void Bidding::clear()
{
    history.clear();
    highest_bid_index.reset();
}

bool Bidding::isBidLegal(const Bid& bid)
{
    if(bid.trump == utils::Trump::PASS || !highest_bid_index.has_value())
    {
        return true;
    }

    return bid > history[highest_bid_index.value()];
}

std::optional<Position> Bidding::getDeclarer()
{
    if(!highest_bid_index)
    {
        return std::nullopt;
    }
    
    std::optional declarer = probable_declarer;
    for (int ind = highest_bid_index.value() - 2; ind >= 0; ind -= 4)
    {
        if (history[ind].trump == history[highest_bid_index.value()].trump)
        {
            declarer = getPartnerPosition(probable_declarer);
        }
    }

    return declarer;
}

std::optional<Bid> Bidding::getContract()
{
    if(highest_bid_index.has_value())
    {
        return std::make_optional(history[highest_bid_index.value()]);
    } else 
    {
        return std::nullopt;
    }
}

};