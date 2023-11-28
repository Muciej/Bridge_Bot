#include <utils/Game.hpp>

namespace utils
{

Trick Game::getCurentTrick()
{
    return tricks[current_trick];
}

int Game::getScore()
{
    // TODO implement
    return 0;
}

std::pair<Position, Position> Game::getWinners()
{
    if(contract == Bid(Trump::PASS, 0)) // edge case when game ended with 4 passes
    {
        return std::pair(Position::NORTH, Position::SOUTH);
    }
    if(dealer_won_tricks > 6 + contract.deal)
    {
        return std::pair(declarer, getPartnerPosition(declarer));
    } else
    {
        return getEnemiesPositions(declarer);
    }
}

}; // namespace utils
