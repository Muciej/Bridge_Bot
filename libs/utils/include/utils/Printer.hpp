#pragma once
#include <vector>
#include <utils/Card.hpp>
#include <utils/Player.hpp>

namespace printer
{

std::string printHand(const std::vector<utils::Card>& hand);
std::string printSortedHand(std::vector<utils::Card> hand);
std::string printPosition(const utils::Position& pos);
std::string printSuit(const utils::Suit& suit);

} // namespace printer
