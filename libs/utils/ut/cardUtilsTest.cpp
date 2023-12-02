#include <gtest/gtest.h>
#include <utils/Card.hpp>
#include <utils/CardsUtils.hpp>

using utils::Card;
using utils::Suit;
using utils::RoyalRank;

namespace
{
    const std::vector<Card> example_hand = {Card(3, Suit::DIAMONDS), Card(5, Suit::DIAMONDS), Card(8, Suit::DIAMONDS), Card(RoyalRank::JACK, Suit::DIAMONDS),
                                            Card(5, Suit::SPADES), Card(7, Suit::SPADES), Card(RoyalRank::QUEEN, Suit::SPADES), Card(RoyalRank::KING, Suit::SPADES),
                                            Card(5, Suit::HEARTS), Card(9, Suit::HEARTS)};

    const std::vector<Card> example_hand_without_spades_7 = {Card(3, Suit::DIAMONDS), Card(5, Suit::DIAMONDS), Card(8, Suit::DIAMONDS), Card(RoyalRank::JACK, Suit::DIAMONDS),
                                                             Card(5, Suit::SPADES), Card(RoyalRank::QUEEN, Suit::SPADES), Card(RoyalRank::KING, Suit::SPADES),
                                                             Card(5, Suit::HEARTS), Card(9, Suit::HEARTS)};
}

TEST(CardUtilsTest, drawCardFromHandExistingCardTest)
{
    auto hand = example_hand;
    utils::drawCardFromHand(hand, Card(7, Suit::SPADES));
    EXPECT_EQ(hand, example_hand_without_spades_7);
}

TEST(CardUtilsTest, drawCardFromHandNonExistingCardTest)
{
    auto hand = example_hand;
    utils::drawCardFromHand(hand, Card(10, Suit::SPADES));
    EXPECT_EQ(hand, example_hand);
}

TEST(CardUtilsTest, isCardInHandFalseTest)
{
    auto hand = example_hand;
    EXPECT_FALSE(utils::isCardInHand(hand, Card(RoyalRank::QUEEN, Suit::DIAMONDS)));
}

TEST(CardUtilsTest, isCardInHandTrueTest)
{
    auto hand = example_hand;
    EXPECT_TRUE(utils::isCardInHand(hand, Card(RoyalRank::JACK, Suit::DIAMONDS)));
}