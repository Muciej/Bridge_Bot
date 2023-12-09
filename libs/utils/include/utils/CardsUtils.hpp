#pragma once
#include <utils/Card.hpp>
#include <vector>

namespace utils
{

void drawCardFromHand(std::vector<Card>& hand, const Card& card_to_draw);
bool isCardInHand(const std::vector<Card> hand, const Card& card);
int getCardAsInt(const Card& card);

} // namespace utils
