#pragma once
#include <utils/Card.hpp>
#include <utils/Player.hpp>
#include <utils/Bid.hpp>

namespace utils
{

/// @brief Struct encapsulating trick
/// note: indexes in played_cards table correspond to int
/// values of utils::Postion enum
struct Trick
{
    utils::Position first;
    utils::Suit suit;
    utils::Card played_cards[4];
    utils::Position winner;
};


/// @brief Function determining winner of the trick
/// the winner is saved to Trick object
/// @param trick - trick object (all players must have played card)
/// @param trump - trump of the current game
void setWinner(Trick& trick, utils::Trump trump);

};
