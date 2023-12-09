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
    return std::find(hand.begin(), hand.end(), card) != hand.end();
}

/// @brief Function that converts card to int number. It is used in bot in order to
/// allow representing cards as ints from 0 to 51.
/// Each number is unique for a card.
/// @param card - card to be converted to int
/// @return - int representing given card
int getCardAsInt(const Card& card)
{
    return ( (static_cast<int>(card.suit) * 13) + static_cast<int>(card.rank) - 2);
}

Card getCardFromInt(int card_int)
{
    char rank = (card_int % 13) + 2;
    Suit suit = static_cast<Suit>(card_int / 13);
    return Card(rank, suit);
}

} // namespace utils
