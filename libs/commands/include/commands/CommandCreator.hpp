#pragma once
#include <string>
#include <utils/Bid.hpp>
#include <utils/Player.hpp>
#include <utils/Card.hpp>

namespace commands
{

using std::string;

class CommandCreator
{
    public:
    string serverGetSetPositionCommand(const string& name, const utils::Position& position);
    string serverGetCardsInfoCommand(const utils::Position& position, std::vector<utils::Card>& hand);
    string serverGetStartBiddingCommand(const utils::Position& dealer_position);
    string serverGetBidInfoCommand(const utils::Position& position, const utils::Bid& bid);
    string serverGetBidEndCommand(const utils::Position& position, const utils::Bid& deal);
    string serverGetPlayCommand(const utils::Position& position, const utils::Card& played_card);
    string serverGetGameEndCommand(const utils::Position& winner_1, const utils::Position& winner_2, int points_won);
    string serverGetErrorMsgAllCommand(const string& msg);
    string serverGetErrorMsgCommand(const utils::Position& position, const string& msg);
};

};
