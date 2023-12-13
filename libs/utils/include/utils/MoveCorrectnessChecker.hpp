#pragma once
#include <utils/Player.hpp>
#include <utils/Trick.hpp>

namespace utils
{

/// @brief Functions verifying if move is legal within given trick
/// @param player - player who placed card
/// @param card_placed - card which has been played
/// @param trick - current trick
/// @return true if move is legal, false otherwise
bool isMoveLegal(const Player& player, const Card& card_played, const Trick& trick);

};
