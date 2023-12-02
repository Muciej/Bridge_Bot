#include <ostream>
#include <utils/Printer.hpp>
#include <utils/Card.hpp>
#include <algorithm>

namespace printer
{

void printHand(std::ostream& stream, const std::vector<utils::Card>& hand)
{
    for(const auto& card : hand)
    {
        stream << card << " ";
    }
}

void printSortedHand(std::ostream& stream, std::vector<utils::Card> hand)
{
    std::sort(hand.begin(), hand.end());
    printHand(stream, hand);
}

} // namespace printer
