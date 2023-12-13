#pragma once
#include <utils/Card.hpp>
#include <vector>

namespace utils
{

/// @brief Removes card from given hand if it is present
/// @param hand - vector of Card objects
/// @param card_to_draw - Card equal to one that should be removed
void drawCardFromHand(std::vector<Card>& hand, const Card& card_to_draw);

/// @brief Checks if given card is in given hand
/// @param hand - vector of Card object
/// @param card - Card equal to one that should be removed 
/// @return true if card is in hand and false otherwise
bool isCardInHand(const std::vector<Card> hand, const Card& card);

/// @brief Converts card represented by Card object to int
/// @return int representing given card
int getCardAsInt(const Card& card);

/// @brief Converts card represented by int to Card object
/// @param card_int - int representation of Card
/// @return Card object representing the same card
Card getCardFromInt(int card_int);

/// @brief Checks suit of card represented as int
/// @param card_int - card to get Suit from
/// @return Suit of given card
Suit getSuitFromIntCard(int card_int);

} // namespace utils
