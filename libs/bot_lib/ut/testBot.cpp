#include <memory>
#include <gtest/gtest.h>
#include <bot_lib/Bot.hpp>
#include <connection/FakeClient.hpp>
#include <utility>
#include <string>
#include <vector>

using bot::Bot;

TEST(BotTest, SetPosCommandReactionTest)
{
    auto client_ptr = std::make_unique<connection::FakeClient>();
    Bot bot("Bot_test", std::move(client_ptr));

    std::vector<std::string> command_data{"SETPOS", "Bot_test", "EAST"};
    bot.executeSetPosCommand(command_data);
    EXPECT_EQ(bot.global_game_state.bot_name, "EAST");

    command_data = std::vector<std::string>{"SETPOS", "Player", "NORTH"};
    bot.executeSetPosCommand(command_data);
    EXPECT_EQ(bot.global_game_state.bot_name, "EAST");
}

