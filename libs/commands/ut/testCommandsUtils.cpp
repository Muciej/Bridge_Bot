#include <gtest/gtest.h>
#include <string>
#include <stdexcept>
#include <commands/CommandsUtils.hpp>
#include <utils/Player.hpp>
#include <utils/Card.hpp>

TEST(CommandUtilsTest, GetPositionFromStringValidStringTest)
{
    std::string command = "NORTH";
    EXPECT_EQ(commands::getPositionFromString(command) ,utils::Position::NORTH);
    command = "SOUTH";
    EXPECT_EQ(commands::getPositionFromString(command) ,utils::Position::SOUTH);
    command = "EAST";
    EXPECT_EQ(commands::getPositionFromString(command) ,utils::Position::EAST);
    command = "WEST";
    EXPECT_EQ(commands::getPositionFromString(command) ,utils::Position::WEST);
}

TEST(CommandUtilsTest, GetPositionFromStringInvalidStringTest)
{
    std::string command = "NARNIA";
    EXPECT_THROW(commands::getPositionFromString(command), std::runtime_error);
}

TEST(CommandUtilsTest, CommandParseCorrectCommandTest)
{
    std::string command = "TEST ONE TWO THREE";
    std::vector<std::string> command_data;
    command = commands::parseCommand(command, command_data);

    std::vector<std::string> test_data{"TEST", "ONE", "TWO", "THREE"};
    EXPECT_EQ(command, "TEST");
    EXPECT_EQ(command_data, test_data);
}

TEST(CommandUtilsTest, CommandParseSpaceEndedTest)
{
    std::string command = "SPACE AT THE END ";
    std::vector<std::string> command_data;
    command = commands::parseCommand(command, command_data);

    std::vector<std::string> test_data{"SPACE", "AT", "THE", "END"};
    EXPECT_EQ(command, "SPACE");
    EXPECT_EQ(command_data, test_data);
}

TEST(CommandUtilsTest, ParseBidCommandPassTest)
{
    std::vector<std::string> test_data = {"BID", "NORTH", "PASS", "0"};
    auto bid = commands::parseBidCommand(test_data);
    EXPECT_EQ(bid, utils::Bid(utils::Trump::PASS, 0));
}

TEST(CommandUtilsTest, ParseBidCommandNoTrumpBidTest)
{
    std::vector<std::string> test_data = {"BID", "SOUTH", "NO_TRUMP", "4"};
    auto bid = commands::parseBidCommand(test_data);
    EXPECT_EQ(bid, utils::Bid(utils::Trump::NO_TRUMP, 4));
}

TEST(CommandUtilsTest, ParseBidCommandSuitBidTest)
{
    std::vector<std::string> test_data = {"BID", "NORTH", "CLUBS", "3"};
    auto bid = commands::parseBidCommand(test_data);
    EXPECT_EQ(bid, utils::Bid(utils::Trump::CLUBS, 3));
}

TEST(CommandUtilsTest, ParsePlayCommandRoyalTest)
{
    std::vector<std::string> test_data = {"PLAY", "NORTH", "♦A"};
    auto card = commands::parsePlayCommand(test_data);
    EXPECT_EQ(card, utils::Card(utils::RoyalRank::ACE, utils::Suit::DIAMONDS));
}

TEST(CommandUtilsTest, ParseBidCommandPassSuitBidTest)
{
    std::vector<std::string> test_data = {"PLAY", "NORTH", "♠3"};
    auto card = commands::parsePlayCommand(test_data);
    EXPECT_EQ(card, utils::Card(3, utils::Suit::SPADES));
}

TEST(CommandUtilsTest, GetCardFromStringNonRoyalRankTest)
{
    std::string card_str = "♠3";
    auto card = commands::getCardFromString(card_str);
    EXPECT_EQ(card, utils::Card(3, utils::Suit::SPADES));
}

TEST(CommandUtilsTest, GetCardFromStringRoyalRankTest)
{
    std::string card_str = "♣Q";
    auto card = commands::getCardFromString(card_str);
    EXPECT_EQ(card, utils::Card(utils::RoyalRank::QUEEN, utils::Suit::CLUBS));
}
