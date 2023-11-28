#pragma once
#include <utils/Player.hpp>
#include <utils/Trick.hpp>

namespace utils
{

bool isMoveLegal(const Player& player, const Card& card_played, const Trick& trick);

};
