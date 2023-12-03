#include <sstream>
#include <algorithm>
#include <utils/Printer.hpp>
#include <utils/Card.hpp>

namespace printer
{

std::string printHand(const std::vector<utils::Card>& hand)
{
    std::stringstream ss;
    for(const auto& card : hand)
    {
        ss << card << " ";
    }
    return ss.str();
}

std::string printSortedHand(std::vector<utils::Card> hand)
{
    std::sort(hand.begin(), hand.end());
    return printHand(hand);
}

} // namespace printer
