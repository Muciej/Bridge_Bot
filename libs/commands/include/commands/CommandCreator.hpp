#pragma once
#include <string>
#include <utils/Bid.hpp>
#include <utils/Player.hpp>
#include <utils/Card.hpp>

namespace commands
{

using std::string;

/// @brief Class responsible for preparing valid commands that can be sent to clients and server
class CommandCreator
{
    public:
    string serverGetSetPositionCommand(const string& name, const utils::Position& position);
    string serverGetCardsInfoCommand(const utils::Position& position, std::vector<utils::Card>& hand);
    string serverGetDummyCardInfoCommand(const utils::Position& dummy_position, std::vector<utils::Card>& hand);
    string serverGetStartBiddingCommand(const utils::Position& dealer_position);
    string serverGetBidEndCommand(const utils::Position& position, const utils::Bid& bid);
    string serverGetTrickResultCommand(const utils::Position& winner);
    string serverGetGameEndCommand(const utils::Position& winner_1, const utils::Position& winner_2, int points_won);
    string serverGetErrorMsgAllCommand(const string& msg);
    string serverGetErrorMsgCommand(const utils::Position& position, const string& msg);

    string getBidInfoCommand(const utils::Position& position, const utils::Bid& bid);
    string getPlayCommand(const utils::Position& position, const utils::Card& played_card);

    string clientGetPlayerAddCommand(const string name, bool isBot);
};

};
