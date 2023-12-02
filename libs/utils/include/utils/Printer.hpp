#pragma once
#include <vector>
#include <utils/Card.hpp>

namespace printer
{

void printHand(std::ostream& stream, const std::vector<utils::Card>& hand);
void printSortedHand(std::ostream& stream, std::vector<utils::Card> hand);

} // namespace printer
