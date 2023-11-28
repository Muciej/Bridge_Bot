#include <gtest/gtest.h>
#include <utils/MoveCorrectnessChecker.hpp>
#include <utils/Trick.hpp>
#include <utils/Card.hpp>
#include <utils/Player.hpp>

using utils::Trick;
using utils::Card;
using utils::isMoveLegal;
using utils::Position;
using utils::Suit;
using utils::Player;
using utils::RoyalRank;

namespace
{
    Player getPlayerWithoutClubsEx()
    {
        auto player_ex = Player("JACK", Position::NORTH, false);
        player_ex.hand = {Card(3, Suit::DIAMONDS), Card(5, Suit::DIAMONDS), Card(8, Suit::DIAMONDS), Card(RoyalRank::JACK, Suit::DIAMONDS),
                          Card(5, Suit::SPADES), Card(7, Suit::SPADES), Card(RoyalRank::QUEEN, Suit::SPADES), Card(RoyalRank::KING, Suit::SPADES),
                          Card(5, Suit::HEARTS), Card(9, Suit::HEARTS)};
        return player_ex;
    }

    Trick getDiamondsIncompleteTrickExample()
    {
        Trick trick;
        trick.first = Position::SOUTH;
        trick.suit = Suit::DIAMONDS;
        trick.played_cards[Position::SOUTH] = Card(8, Suit::DIAMONDS);
        trick.played_cards[Position::WEST] = Card(10, Suit::DIAMONDS);
        return trick;
    }

    Trick getClubsIncompleteTrickExample()
    {
        Trick trick;
        trick.first = Position::WEST;
        trick.suit = Suit::CLUBS;
        trick.played_cards[Position::WEST] = Card(RoyalRank::JACK, Suit::CLUBS);
        return trick;
    }

}

TEST(MoveCorrectnessCheckerTests, MoveInTrumpColorWithNotOwnedCardTest)
{
    auto player = getPlayerWithoutClubsEx();
    auto trick = getDiamondsIncompleteTrickExample();

    ASSERT_FALSE(isMoveLegal(player, Card(RoyalRank::KING, Suit::DIAMONDS), trick));
}

TEST(MoveCorrectnessCheckerTests, MoveInTrumpColorWithOwnedCardTest)
{
    auto player = getPlayerWithoutClubsEx();
    auto trick = getDiamondsIncompleteTrickExample();

    ASSERT_TRUE(isMoveLegal(player, Card(RoyalRank::JACK, Suit::DIAMONDS), trick));
}

TEST(MoveCorrectnessCheckerTests, LegalMoveInOtherColorWithOwnedCardTest)
{
    auto player = getPlayerWithoutClubsEx();
    auto trick = getClubsIncompleteTrickExample();

    ASSERT_TRUE(isMoveLegal(player, Card(7, Suit::SPADES), trick));
}

TEST(MoveCorrectnessCheckerTests, LegalMoveInOtherColorWithNotOwnedCardTest)
{
    auto player = getPlayerWithoutClubsEx();
    auto trick = getClubsIncompleteTrickExample();

    ASSERT_FALSE(isMoveLegal(player, Card(2, Suit::SPADES), trick));
}

TEST(MoveCorrectnessCheckerTests, IllegalMoveInOtherColorWithOwnedCardTest)
{
    auto player = getPlayerWithoutClubsEx();
    auto trick = getDiamondsIncompleteTrickExample();

    ASSERT_FALSE(isMoveLegal(player, Card(5, Suit::SPADES), trick));
}

TEST(MoveCorrectnessCheckerTests, IllegalMoveInOtherColorWithNotOwnedCardTest)
{
    auto player = getPlayerWithoutClubsEx();
    auto trick = getDiamondsIncompleteTrickExample();

    ASSERT_FALSE(isMoveLegal(player, Card(6, Suit::SPADES), trick));
}