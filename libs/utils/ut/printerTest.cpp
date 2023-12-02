#include <vector>
#include <gtest/gtest.h>
#include <utils/Printer.hpp>
#include <utils/Card.hpp>
#include <sstream>
#include <string>

using utils::Suit;
using utils::Card;
using utils::RoyalRank;

namespace
{
    const std::vector<Card> example_hand = {Card(3, Suit::DIAMONDS), Card(RoyalRank::KING, Suit::SPADES), Card(5, Suit::DIAMONDS), Card(8, Suit::CLUBS),
                                            Card(RoyalRank::JACK, Suit::DIAMONDS), Card(7, Suit::HEARTS), Card(RoyalRank::QUEEN, Suit::SPADES),
                                            Card(5, Suit::HEARTS), Card(RoyalRank::ACE, Suit::CLUBS)};
    const std::string expected_non_sorted = "♦3 ♠K ♦5 ♣8 ♦J ♥7 ♠Q ♥5 ♣A ";
    const std::string expected_sorted = "♣8 ♣A ♦3 ♦5 ♦J ♥5 ♥7 ♠Q ♠K ";
}

TEST(PrinterTest, PrintEmptyHandTest)
{
    std::vector<Card> hand;
    std::stringstream ss;
    printer::printHand(ss, hand);
    EXPECT_EQ(ss.str(), "");
}

TEST(PrinterTest, SortedPrintEmptyHandTest)
{
    std::vector<Card> hand;
    std::stringstream ss;
    printer::printSortedHand(ss, hand);
    EXPECT_EQ(ss.str(), "");
}

TEST(PrinterTest, PrintNonEmptyHandTest)
{
    auto hand = example_hand;
    std::stringstream ss;
    printer::printHand(ss, hand);
    EXPECT_EQ(ss.str(), expected_non_sorted);
}

TEST(PrinterTest, SortedPrintNonEmptyHandTest)
{
    auto hand = example_hand;
    std::stringstream ss;
    printer::printSortedHand(ss, hand);
    EXPECT_EQ(ss.str(), expected_sorted);
}