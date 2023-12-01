#include <vector>
#include <algorithm>
#include <utils/CardsUtils.hpp>
#include <utils/Card.hpp>

namespace utils
{

void drawCardFromHand(std::vector<Card>& hand, const Card& card_to_draw)
{
    auto newEnd = std::remove(hand.begin(), hand.end(), card_to_draw);
    hand.erase(newEnd, hand.end());
}

bool isCardInHand(const std::vector<Card> hand, const Card& card)
{
    return std::find(hand.begin(), hand.end(), card) == hand.end();
}

} // namespace utils
