#include <gtest/gtest.h>
#include <vector>
#include <memory>
#include <utils/Player.hpp>
#include <bot_lib/bot_utils/Move.hpp>
#include <bot_lib/bot_utils/GameState.hpp>
#include <bot_lib/moves_optimizations/MergeRepeatingCards.hpp>
#include <bot_lib/moves_optimizations/MergeSuccessingCards.hpp>

using bot::Move;
using utils::Card;

namespace
{

const std::vector<Move> moves_without_repetitions{ Move(10), Move(24), Move(49), Move(12), Move(15), Move(21)};
const std::vector<Move> moves_with_repetitions{Move(10), Move(24), Move(49), Move(24), Move(15), Move(49)};
const std::vector<Move> moves_with_repetitions_cleaned{Move(10), Move(24), Move(49), Move(15)};
const std::vector<Move> moves_without_successing{Move(10), Move(24), Move(49), Move(12), Move(15), Move(21)};
const std::vector<Move> moves_with_successing{Move(10), Move(24), Move(25), Move(26), Move(15), Move(21), Move(22), Move(15)};
const std::vector<Move> moves_with_successing_cleaned{Move(10), Move(25), Move(26), Move(15), Move(22), Move(15)};
const std::vector<Move> moves_with_successing_and_repeating{Move(10), Move(24), Move(49), Move(12), Move(15), Move(21), Move(24), Move(49), Move(25), Move(26), Move(27)};
const std::vector<Move> moves_with_successing_and_repeating_cleaned{Move(10), Move(49), Move(12), Move(15), Move(21), Move(25), Move(27)};

} // namespace


TEST(MoveOptimizersTests, MergeRepeatingCardsNoRepeatingCards)
{
    bot::MergeRepeatingCards merge_repeating;
    auto test_data = moves_without_repetitions;
    merge_repeating.handle(test_data);
    EXPECT_EQ(test_data, moves_without_repetitions);
}

TEST(MoveOptimizersTests, MergeRepeatingCardsDeleteRepeatingCards)
{
    bot::MergeRepeatingCards merge_repeating;
    auto test_data = moves_with_repetitions;
    merge_repeating.handle(test_data);
    EXPECT_EQ(test_data, moves_with_repetitions_cleaned);
}

TEST(MoveOptimizersTests, MergeSuccessingCardsNoSuccessingCards)
{
    bot::MergeSuccessingCards merge_successing;
    auto test_data = moves_without_successing;
    merge_successing.handle(test_data);
    EXPECT_EQ(test_data, moves_without_successing);
}

TEST(MoveOptimizersTests, MergeSuccessingCardsDeleteSuccessingCards)
{
    bot::MergeSuccessingCards merge_successing;
    auto test_data = moves_with_successing;
    merge_successing.handle(test_data);
    EXPECT_EQ(test_data, moves_with_successing_cleaned);
}

TEST(MoveOptimizersTests, TestChain)
{
    bot::MergeRepeatingCards merge_repeating;
    merge_repeating.setNext(std::make_unique<bot::MergeSuccessingCards>());
    auto test_data = moves_with_successing_and_repeating;
    merge_repeating.handle(test_data);
    EXPECT_EQ(test_data, moves_with_successing_and_repeating_cleaned);
}
