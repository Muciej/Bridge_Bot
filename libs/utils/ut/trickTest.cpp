#include <gtest/gtest.h>
#include <utils/Trick.hpp>
#include <utils/Card.hpp>
#include <utils/Player.hpp>

using utils::Trick;
using utils::Position;
using utils::Card;
using utils::Suit;
using utils::Trump;

TEST(TrickTest, SetWinnerTrumpTrickTest)
{
    Trick trick;
    trick.first = Position::NORTH;
    trick.suit = Suit::HEARTS;
    trick.played_cards[Position::NORTH] = Card(utils::RoyalRank::JACK, Suit::HEARTS);
    trick.played_cards[Position::EAST] = Card(4, Suit::SPADES);
    trick.played_cards[Position::SOUTH] = Card(utils::RoyalRank::ACE, Suit::HEARTS);
    trick.played_cards[Position::WEST] = Card(10, Suit::HEARTS);
    utils::setWinner(trick, Trump::HEARTS);
    ASSERT_EQ(trick.winner, Position::SOUTH);
}

TEST(TrickTest, SetWinnerNoTrumpTrickWonBySuitTest)
{
    Trick trick;
    trick.first = Position::NORTH;
    trick.suit = Suit::HEARTS;
    trick.played_cards[Position::NORTH] = Card(utils::RoyalRank::JACK, Suit::HEARTS);
    trick.played_cards[Position::EAST] = Card(4, Suit::SPADES);
    trick.played_cards[Position::SOUTH] = Card(utils::RoyalRank::ACE, Suit::HEARTS);
    trick.played_cards[Position::WEST] = Card(10, Suit::HEARTS);
    utils::setWinner(trick, Trump::CLUBS);
    ASSERT_EQ(trick.winner, Position::SOUTH);
}

TEST(TrickTest, SetWinnerNoTrumpTrickWonByTrumpTest)
{
    Trick trick;
    trick.first = Position::NORTH;
    trick.suit = Suit::HEARTS;
    trick.played_cards[Position::NORTH] = Card(utils::RoyalRank::JACK, Suit::HEARTS);
    trick.played_cards[Position::EAST] = Card(4, Suit::SPADES);
    trick.played_cards[Position::SOUTH] = Card(utils::RoyalRank::ACE, Suit::HEARTS);
    trick.played_cards[Position::WEST] = Card(10, Suit::HEARTS);
    utils::setWinner(trick, Trump::SPADES);
    ASSERT_EQ(trick.winner, Position::EAST);
}

TEST(TrickTest, SetWinnerOnlyOneCardInSuit)
{
    Trick trick;
    trick.first = Position::EAST;
    trick.suit = Suit::SPADES;
    trick.played_cards[Position::NORTH] = Card(utils::RoyalRank::JACK, Suit::HEARTS);
    trick.played_cards[Position::EAST] = Card(4, Suit::SPADES);
    trick.played_cards[Position::SOUTH] = Card(utils::RoyalRank::ACE, Suit::HEARTS);
    trick.played_cards[Position::WEST] = Card(10, Suit::HEARTS);
    utils::setWinner(trick, Trump::CLUBS);
    ASSERT_EQ(trick.winner, Position::EAST);
}

TEST(TrickTest, SetWinnerAllCardsInSuit)
{
    Trick trick;
    trick.first = Position::EAST;
    trick.suit = Suit::SPADES;
    trick.played_cards[Position::NORTH] = Card(utils::RoyalRank::QUEEN, Suit::SPADES);
    trick.played_cards[Position::EAST] = Card(4, Suit::SPADES);
    trick.played_cards[Position::SOUTH] = Card(utils::RoyalRank::JACK, Suit::SPADES);
    trick.played_cards[Position::WEST] = Card(10, Suit::SPADES);
    utils::setWinner(trick, Trump::CLUBS);
    ASSERT_EQ(trick.winner, Position::NORTH);
}

TEST(TrickTest, TempErrorTest)
{
    Trick trick;
    trick.first = Position::EAST;
    trick.suit = Suit::SPADES;
    trick.played_cards[Position::NORTH] = Card(utils::RoyalRank::QUEEN, Suit::SPADES);
    trick.played_cards[Position::EAST] = Card(4, Suit::SPADES);
    trick.played_cards[Position::SOUTH] = Card(utils::RoyalRank::JACK, Suit::SPADES);
    trick.played_cards[Position::WEST] = Card(10, Suit::SPADES);
    utils::setWinner(trick, Trump::CLUBS);
    ASSERT_EQ(trick.winner, Position::NORTH);
}

