#include <optional>
#include <utils/Trick.hpp>
#include <utils/Card.hpp>
#include <utils/Bid.hpp>
#include <stdexcept>

namespace utils
{

std::optional<int> checkBiggestInSuit(const Trick& trick, utils::Suit suit)
{
    std::optional<int> highest;
    for(int i = 0; i < 4; i++)
    {
        if(trick.played_cards[i].suit == suit && (!highest || static_cast<int>(trick.played_cards[i].rank) > static_cast<int>(trick.played_cards[highest.value()].rank)))
        {
            highest = i;
        }
    }
    return highest;
}

utils::Suit getSuitFromValidTrump(const utils::Trump& trump)
{
    switch (trump)
    {
    case utils::Trump::SPADES:
        return utils::Suit::SPADES;
        break;
    case utils::Trump::HEARTS:
        return utils::Suit::HEARTS;
        break;
    case utils::Trump::DIAMONDS:
        return utils::Suit::DIAMONDS;
        break;
    case utils::Trump::CLUBS:
        return utils::Suit::CLUBS;
        break;
    default:
        throw std::runtime_error("Cannot convert this TRUMP to SUIT");
    }
}

void setWinner(Trick& trick, utils::Trump trump)
{
    std::optional<int> big_trump_ind;
    if(trump != utils::Trump::NO_TRUMP)
    {
        big_trump_ind = checkBiggestInSuit(trick, getSuitFromValidTrump(trump));
    }
    auto big_suit = checkBiggestInSuit(trick, trick.suit);

    trick.winner = big_trump_ind ? static_cast<Position>(big_trump_ind.value()) : static_cast<Position>(big_suit.value());
}

}; // namespace utils
