#include <sstream>
#include <gtest/gtest.h>
#include <utils/Card.hpp>

using Cards::Card;
using Cards::Suit;
using Cards::RoyalRank;

TEST(CardsTest, DefaultContructorTest)
{
    Card card;
    ASSERT_EQ(card.rank, 2);
    ASSERT_EQ(card.suit, Suit::CLUBS);
}

TEST(CardsTest, InvalidRankTest)
{
    ASSERT_THROW(Card(15, Suit::CLUBS), std::range_error);
    ASSERT_THROW(Card(1, Suit::CLUBS), std::range_error);
}

TEST(CardsTest, NonRoyalPrintTest)
{
    std::stringstream ss;
    std::string s;
    Card card(10, Suit::HEARTS);
    ss<<card;
    ss>>s;
    ASSERT_EQ(s, "♥10");
    ss.clear();

    card = Card(2, Suit::DIAMONDS);
    ss<<card;
    ss>>s;
    ASSERT_EQ(s, "♦2");
    ss.clear();
}

TEST(CardsTest, RoyalPrintTest)
{
    std::stringstream ss;
    std::string s;

    Card card(11, Suit::HEARTS);
    ss<<card;
    ss>>s;
    ASSERT_EQ(s, "♥J");
    ss.clear();

    card = Card(RoyalRank::QUEEN, Suit::HEARTS);
    ss<<card;
    ss>>s;
    ASSERT_EQ(s, "♥Q");
    ss.clear();

    card = Card(13, Suit::HEARTS);
    ss<<card;
    ss>>s;
    ASSERT_EQ(s, "♥K");
    ss.clear();

    card = Card(RoyalRank::ACE, Suit::HEARTS);
    ss<<card;
    ss>>s;
    ASSERT_EQ(s, "♥A");
    ss.clear();
    
}