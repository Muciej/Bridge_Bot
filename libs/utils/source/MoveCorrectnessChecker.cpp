#include <utils/MoveCorrectnessChecker.hpp>
#include <vector>
#include <algorithm>

namespace utils
{

bool isMoveLegal(const Player& player, const Card& card_played, const Trick& trick)
{
    bool has_card = std::find(player.hand.begin(), player.hand.end(), card_played) != player.hand.end();
    if(!has_card)
    {
        return false;
    }
    if(player.position == trick.first || card_played.suit == trick.suit)
    {
        return true;
    } else
    {
        return std::find_if(player.hand.begin(), player.hand.end(), [&trick](const Card& card){ return card.suit == trick.suit; }) == player.hand.end();
    }
}

}; // namespace utils
