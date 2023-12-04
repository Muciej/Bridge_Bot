#include <string>
#include <vector>
#include <gtest/gtest.h>
#include <commands/CommandCreator.hpp>
#include <utils/Player.hpp>
#include <utils/Card.hpp>

TEST(CommandCreatorTest, ServerSetPosCmdTest)
{
    commands::CommandCreator creator;
    const auto cmd = creator.serverGetSetPositionCommand("JACK", utils::Position::EAST);
    ASSERT_EQ(cmd, "SETPOS JACK EAST");
}

TEST(CommandCreatorTest, ServerCardInfoCmdTest)
{
    commands::CommandCreator creator;
    std::vector<utils::Card> hand = {utils::Card(3, utils::Suit::DIAMONDS), utils::Card(5, utils::Suit::DIAMONDS), utils::Card(8, utils::Suit::DIAMONDS),
                                     utils::Card(utils::RoyalRank::JACK, utils::Suit::DIAMONDS), utils::Card(5, utils::Suit::SPADES), utils::Card(7, utils::Suit::SPADES)};
    const auto cmd = creator.serverGetCardsInfoCommand(utils::Position::EAST, hand);
    ASSERT_EQ(cmd, "HAND EAST ♦3 ♦5 ♦8 ♦J ♠5 ♠7");
}

TEST(CommandCreatorTest, ServerBiddingStartCmdTest)
{
    commands::CommandCreator creator;
    const auto cmd = creator.serverGetStartBiddingCommand(utils::Position::SOUTH);
    ASSERT_EQ(cmd, "BIDDER SOUTH");
}

TEST(CommandCreatorTest, ServerBidInfoCmdTest)
{
    commands::CommandCreator creator;
    const auto cmd = creator.getBidInfoCommand(utils::Position::EAST, utils::Bid(utils::Trump::HEARTS, 3));
    ASSERT_EQ(cmd, "BID EAST HEARTS 3");
}

TEST(CommandCreatorTest, ServerBiddingEndCmdTest)
{
    commands::CommandCreator creator;
    const auto cmd = creator.serverGetBidEndCommand(utils::Position::EAST, utils::Bid(utils::Trump::NO_TRUMP, 5));
    ASSERT_EQ(cmd, "BIDEND EAST NO_TRUMP 5");
}

TEST(CommandCreatorTest, ServerPlayCmdTest)
{
    commands::CommandCreator creator;
    const auto cmd = creator.getPlayCommand(utils::Position::EAST, utils::Card(utils::RoyalRank::ACE, utils::Suit::SPADES));
    ASSERT_EQ(cmd, "PLAY EAST ♠A");
}

TEST(CommandCreatorTest, ServerTrickResultCmdTest)
{
    commands::CommandCreator creator;
    const auto cmd = creator.serverGetTrickResultCommand(utils::Position::NORTH);
    ASSERT_EQ(cmd, "TRICKEND NORTH");
}

TEST(CommandCreatorTest, ServerGameEndCmdTest)
{
    commands::CommandCreator creator;
    const auto cmd = creator.serverGetGameEndCommand(utils::Position::EAST, utils::Position::WEST, 10, 240);
    ASSERT_EQ(cmd, "GAMEEND EAST WEST 10 240");
}

TEST(CommandCreatorTest, ServerErrorAllCmdTest)
{
    commands::CommandCreator creator;
    const auto cmd = creator.serverGetErrorMsgAllCommand("Error for all players!");
    ASSERT_EQ(cmd, "ERROR ALL Error for all players!");
}

TEST(CommandCreatorTest, ServerErrorPlayerCmdTest)
{
    commands::CommandCreator creator;
    const auto cmd = creator.serverGetErrorMsgCommand(utils::Position::EAST, "Error for EAST!");
    ASSERT_EQ(cmd, "ERROR EAST Error for EAST!");
}