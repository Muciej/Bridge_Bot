#include <commands/CommandCreator.hpp>

namespace commands
{

    string CommandCreator::serverGetSetPositionCommand(const string& name, const utils::Position& position)
    {
        return "";
    }

    string CommandCreator::serverGetCardsInfoCommand( /*TODO*/ )
    {
        return "";
    }

    string CommandCreator::serverGetStartBiddingCommand(const utils::Position& dealer_position)
    {
        return "";
    }

    string CommandCreator::serverGetBidInfoCommand(const utils::Position& position, const utils::Bid& bid)
    {
        return "";
    }

    string CommandCreator::serverGetBidEndCommand(const utils::Position& position, const utils::Bid& deal)
    {
        return "";
    }

    string CommandCreator::serverGetPlayCommand(const utils::Position& position, const utils::Card& played_card)
    {
        return "";
    }

    string CommandCreator::serverGetGameEndCommand(const utils::Position& winner_1, const utils::Position& winner_2, int points_won)
    {
        return "";
    }

};