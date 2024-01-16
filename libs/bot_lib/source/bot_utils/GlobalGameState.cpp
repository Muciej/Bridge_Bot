#include <bot_lib/bot_utils/GlobalGameState.hpp>
#include <utils/Bid.hpp>

namespace bot
{

utils::Bid getHighestBid(const std::vector<utils::Bid>& bidding_history)
{
    auto biggest = utils::Bid(utils::Trump::PASS, 0);
    if(bidding_history.size() == 0)
        return biggest;
    for(auto it = bidding_history.end()-1; it >= bidding_history.begin(); it--)
    {
        if (*it > biggest)
        {
            biggest = *it;
        }
    }
    return biggest;
}

bool isBiddingEnded(const std::vector<utils::Bid>& bidding_history)
{
    int pass_strike = 0;
    for( auto it = bidding_history.end()-1; it >= bidding_history.begin(); it--)
    {
        if(*it == utils::Bid(utils::Trump::PASS, 0))
        {
            pass_strike++;
        } else
        {
            break;
        }
    }
    if(bidding_history.size() <= 4)
    {
        return pass_strike >= 4;
    } else
    {
        return pass_strike >= 3;
    }
}

} // namespace bot
