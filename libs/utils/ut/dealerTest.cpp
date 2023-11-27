#include <set>
#include <gtest/gtest.h>
#include <utils/Card.hpp>
#include <utils/Dealer.hpp>
#include <iostream>

TEST(DealerTests, TestProperHandSize)
{
    utils::Dealer dealer;
    auto hands = dealer.dealCards();

    for(int i = 0; i<4; i++)
    {
        ASSERT_EQ(hands[i].size(), 13);
    }   
}

TEST(DealerTests, TestPrintHands)
{
    utils::Dealer dealer;
    auto hands = dealer.dealCards();

    for(int i = 0; i<4; i++)
    {
        for(const auto& card : hands[i])
        {
            std::cout << card << ", ";
        }
        std::cout << std::endl;
    }
}
