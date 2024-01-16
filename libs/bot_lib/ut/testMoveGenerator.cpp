#include <gtest/gtest.h>
#include <bot_lib/bot_utils/MovesGenerator.hpp>
#include <bot_lib/bot_utils/GameState.hpp>
#include <utils/Player.hpp>

TEST(MoveGeneratorTests, TurnNumberTest)
{
    bot::MoveGenerator generator;
    bot::GameState state;
    state.tricker = utils::Position::SOUTH;

    EXPECT_EQ(generator.getTurnNumber(state, utils::Position::SOUTH), 1);
    EXPECT_EQ(generator.getTurnNumber(state, utils::Position::WEST), 2);
    EXPECT_EQ(generator.getTurnNumber(state, utils::Position::NORTH), 3);
    EXPECT_EQ(generator.getTurnNumber(state, utils::Position::EAST), 4);

    state.tricker = utils::Position::WEST;
    EXPECT_EQ(generator.getTurnNumber(state, utils::Position::SOUTH), 4);
    EXPECT_EQ(generator.getTurnNumber(state, utils::Position::WEST), 1);
    EXPECT_EQ(generator.getTurnNumber(state, utils::Position::NORTH), 2);
    EXPECT_EQ(generator.getTurnNumber(state, utils::Position::EAST), 3);

    state.tricker = utils::Position::NORTH;
    EXPECT_EQ(generator.getTurnNumber(state, utils::Position::SOUTH), 3);
    EXPECT_EQ(generator.getTurnNumber(state, utils::Position::WEST), 4);
    EXPECT_EQ(generator.getTurnNumber(state, utils::Position::NORTH), 1);
    EXPECT_EQ(generator.getTurnNumber(state, utils::Position::EAST), 2);

    state.tricker = utils::Position::EAST;
    EXPECT_EQ(generator.getTurnNumber(state, utils::Position::SOUTH), 2);
    EXPECT_EQ(generator.getTurnNumber(state, utils::Position::WEST), 3);
    EXPECT_EQ(generator.getTurnNumber(state, utils::Position::NORTH), 4);
    EXPECT_EQ(generator.getTurnNumber(state, utils::Position::EAST), 1);
}