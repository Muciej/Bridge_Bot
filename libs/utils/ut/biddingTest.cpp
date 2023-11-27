#include <optional>
#include <gtest/gtest.h>
#include <utils/Bid.hpp>
#include <utils/Bidding.hpp>

using utils::Bid;
using utils::Bidding;
using utils::Position;
using utils::Trump;
using utils::RoyalRank;

TEST(BiddingTest, ProperInitTest)
{
    Bidding bidding;
    ASSERT_EQ(bidding.getContract(), std::nullopt);
    ASSERT_EQ(bidding.getDeclarer(), std::nullopt);
    ASSERT_FALSE(bidding.isBiddingEnded());
}

TEST(BiddingTest, FourPassesTest)
{
    Bidding bidding;
    bidding.addBid(Position::NORTH, Bid(Trump::PASS, 0));
    ASSERT_FALSE(bidding.isBiddingEnded());
    bidding.addBid(Position::NORTH, Bid(Trump::PASS, 0));
    ASSERT_FALSE(bidding.isBiddingEnded());
    bidding.addBid(Position::NORTH, Bid(Trump::PASS, 0));
    ASSERT_FALSE(bidding.isBiddingEnded());
    bidding.addBid(Position::NORTH, Bid(Trump::PASS, 0));
    ASSERT_TRUE(bidding.isBiddingEnded());
}

TEST(BiddingTest, NormalBiddingTest)
{
    Bidding bidding;
    bidding.addBid(Position::NORTH, Bid(Trump::PASS, 0));
    ASSERT_FALSE(bidding.isBiddingEnded());
    bidding.addBid(Position::EAST, Bid(Trump::HEARTS, 1));
    ASSERT_FALSE(bidding.isBiddingEnded());
    bidding.addBid(Position::SOUTH, Bid(Trump::SPADES, 1));
    ASSERT_FALSE(bidding.isBiddingEnded());
    bidding.addBid(Position::WEST, Bid(Trump::DIAMONDS, 2));
    ASSERT_FALSE(bidding.isBiddingEnded());
    bidding.addBid(Position::NORTH, Bid(Trump::PASS, 0));
    ASSERT_FALSE(bidding.isBiddingEnded());
    bidding.addBid(Position::EAST, Bid(Trump::PASS, 0));
    ASSERT_FALSE(bidding.isBiddingEnded());
    bidding.addBid(Position::SOUTH, Bid(Trump::PASS, 0));

    ASSERT_TRUE(bidding.isBiddingEnded());
    ASSERT_EQ(bidding.getContract(), Bid(Trump::DIAMONDS, 2));
    ASSERT_EQ(bidding.getDeclarer(), Position::WEST);

}

TEST(BiddingTest, InvalidBidTest)
{
    Bidding bidding;
    ASSERT_ANY_THROW(bidding.addBid(Position::EAST, Bid(Trump::CLUBS, 0)));
    ASSERT_ANY_THROW(bidding.addBid(Position::EAST, Bid(Trump::CLUBS, 8)));
}

TEST(BiddingTest, WrongBidTest)
{
    Bidding bidding;
    ASSERT_TRUE(bidding.addBid(Position::EAST, Bid(Trump::DIAMONDS, 2)));
    ASSERT_FALSE(bidding.addBid(Position::SOUTH, Bid(Trump::CLUBS, 1)));
    ASSERT_FALSE(bidding.addBid(Position::WEST, Bid(Trump::CLUBS, 2)));
    ASSERT_FALSE(bidding.addBid(Position::NORTH, Bid(Trump::DIAMONDS, 2)));
}

TEST(BiddingTest, SameColourDeclalerHandlingTest)
{
    Bidding bidding;
    bidding.addBid(Position::EAST, Bid(Trump::DIAMONDS, 2));
    bidding.addBid(Position::SOUTH, Bid(Trump::HEARTS, 2));
    bidding.addBid(Position::WEST, Bid(Trump::DIAMONDS, 3));
    bidding.addBid(Position::NORTH, Bid(Trump::PASS, 0));
    bidding.addBid(Position::EAST, Bid(Trump::PASS, 0));
    bidding.addBid(Position::SOUTH, Bid(Trump::PASS, 0));
    ASSERT_EQ(bidding.getDeclarer(), Position::EAST);
}

TEST(BiddingTest, LongBiddingTest)
{
    Bidding bidding;
    bidding.addBid(Position::SOUTH, Bid(Trump::PASS, 0));
    bidding.addBid(Position::WEST, Bid(Trump::DIAMONDS, 1));
    bidding.addBid(Position::NORTH, Bid(Trump::HEARTS, 1));
    bidding.addBid(Position::EAST, Bid(Trump::CLUBS, 2));
    bidding.addBid(Position::SOUTH, Bid(Trump::SPADES, 2));
    bidding.addBid(Position::WEST, Bid(Trump::PASS, 0));
    bidding.addBid(Position::NORTH, Bid(Trump::HEARTS, 3));
    bidding.addBid(Position::EAST, Bid(Trump::PASS, 0));
    bidding.addBid(Position::SOUTH, Bid(Trump::NO_TRUMP, 3));
    bidding.addBid(Position::WEST, Bid(Trump::PASS, 0));
    bidding.addBid(Position::NORTH, Bid(Trump::PASS, 0));
    bidding.addBid(Position::EAST, Bid(Trump::CLUBS, 5));
    bidding.addBid(Position::SOUTH, Bid(Trump::NO_TRUMP, 6));
    bidding.addBid(Position::WEST, Bid(Trump::PASS, 0));
    bidding.addBid(Position::NORTH, Bid(Trump::SPADES, 7));
    bidding.addBid(Position::EAST, Bid(Trump::PASS, 0));
    bidding.addBid(Position::SOUTH, Bid(Trump::PASS, 0));
    bidding.addBid(Position::WEST, Bid(Trump::PASS, 0));

    ASSERT_TRUE(bidding.isBiddingEnded());
    ASSERT_EQ(bidding.getContract(), Bid(Trump::SPADES, 7));
    ASSERT_EQ(bidding.getDeclarer(), Position::SOUTH);
}