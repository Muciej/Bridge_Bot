#pragma once
#include <vector>
#include <utils/Card.hpp>
#include <utils/Player.hpp>

namespace printer
{

/// @brief Returns string with printed cards in hand
/// @param hand - vector of Card objects
/// @return - string in form e.g.: ♥3 ♥2 ♥K ♥J ♣5 ♣3 
std::string printHand(const std::vector<utils::Card>& hand);

/// @brief Returns string with printed cards in ascending order
/// @param hand - vector of Card objects
/// @return - string in form e.g.: ♣3 ♣5 ♣10 ♥3 ♥K
std::string printSortedHand(std::vector<utils::Card> hand);

/// @brief Returns string with printed position
/// @param pos - Position object to print
/// @return - string in form e.g.: WEST
std::string printPosition(const utils::Position& pos);

/// @brief Returns string with printed suit
/// @param pos - Suit object to print
/// @return - string in form e.g.: SPADES
std::string printSuit(const utils::Suit& suit);

} // namespace printer
