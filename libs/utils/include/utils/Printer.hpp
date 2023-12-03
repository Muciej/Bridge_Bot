#pragma once
#include <vector>
#include <utils/Card.hpp>

namespace printer
{

std::string printHand(const std::vector<utils::Card>& hand);
std::string printSortedHand(std::vector<utils::Card> hand);

} // namespace printer
