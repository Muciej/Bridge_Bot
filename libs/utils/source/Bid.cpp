#include <utils/Bid.hpp>

namespace utils
{

Bid::Bid(const Trump& _trump, const int& _deal) : trump(_trump)
{
    if (_trump != Trump::PASS && (_deal < 1 || _deal > 7))
    {
        throw std::range_error("Wrong deal!");
    } else
    {
        trump = _trump;
        deal = _deal;
    }
}

bool operator==(const Bid& b1, const Bid& b2)
{
    return b1.deal == b2.deal && b1.trump == b2.trump;
}

bool operator<(const Bid& b1, const Bid& b2)
{
    if(b1.deal < b2.deal)
    {
        return true;
    } else if(b1.deal == b2.deal && static_cast<int>(b1.trump) < static_cast<int>(b2.trump))
    {
        return true;
    } else 
    {
        return false;
    }
}

bool operator>(const Bid& b1, const Bid& b2)
{
    return b2 < b1;
}

};
