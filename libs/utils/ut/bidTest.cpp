#include <gtest/gtest.h>
#include <utils/Bid.hpp>
#include <stdexcept>

using utils::Bid;
using utils::Trump;

TEST(BidTest, SimpleBidCreation)
{
    Bid b(Trump::DIAMONDS, 3);
    ASSERT_EQ(b.deal, 3);
    ASSERT_EQ(b.trump, Trump::DIAMONDS);
}

TEST(BidTest, TooHighDeal)
{
    ASSERT_THROW(Bid(Trump::DIAMONDS, 8), std::range_error);
}

TEST(BidTest, TooLowDeal)
{
    ASSERT_THROW(Bid(Trump::DIAMONDS, 0), std::range_error);
}

TEST(BidTest, EqualOperator)
{
    Bid b1(Trump::DIAMONDS, 3);
    Bid b2(Trump::DIAMONDS, 3);
    ASSERT_TRUE(b1 == b2);

    Bid b3(Trump::DIAMONDS, 4);
    Bid b4(Trump::HEARTS, 3);
    ASSERT_FALSE(b1 == b3);
    ASSERT_FALSE(b1 == b4);
}

TEST(BidTest, MoreLessOperator)
{
    Bid b1(Trump::HEARTS, 4);
    Bid b2(Trump::HEARTS, 3);

    ASSERT_TRUE(b1 > b2);
    ASSERT_FALSE(b1 < b2);

    Bid b3(Trump::SPADES, 3);
    ASSERT_TRUE(b3 > b2);
    ASSERT_TRUE(b1 > b3);
    ASSERT_FALSE(b3 < b2);
    ASSERT_FALSE(b1 < b3);    
}