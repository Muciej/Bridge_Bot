#include <utility>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>
#include <bot_lib/Bot.hpp>
#include <connection/FakeClient.hpp>
#include <utils/Card.hpp>

using bot::Bot;
using utils::Card;
using utils::Suit;
using utils::RoyalRank;

namespace
{

const std::vector<Card> example_hand = {Card(3, Suit::DIAMONDS), Card(5, Suit::DIAMONDS), Card(8, Suit::DIAMONDS), Card(RoyalRank::JACK, Suit::DIAMONDS),
                                    Card(5, Suit::SPADES), Card(7, Suit::SPADES), Card(RoyalRank::QUEEN, Suit::SPADES), Card(RoyalRank::KING, Suit::SPADES),
                                    Card(5, Suit::HEARTS), Card(9, Suit::HEARTS)};

const std::vector<std::string> example_hand_command_south = {"HAND", "SOUTH", "♦3", "♦5", "♦8", "♦J", "♥5", "♥7", "♥J", "♠5", "♠7", "♣8", "♣9", "♣K", "♣A"};

const std::vector<int> example_hand_int_values = {14, 16, 19, 22, 29, 31, 35, 42, 44, 6, 7, 11, 12};
}

TEST(BotTest, ConstructionDestrucionTest)
{
    auto client_ptr = std::make_unique<connection::FakeClient>();
    Bot bot("Bot_test", std::move(client_ptr));
    EXPECT_EQ(bot.global_game_state.bot_name, "Bot_test");
}

TEST(BotTest, SetPosCommandReactionTest)
{
    auto client_ptr = std::make_unique<connection::FakeClient>();
    Bot bot("Bot_test", std::move(client_ptr));

    std::vector<std::string> command_data{"SETPOS", "Bot_test", "EAST"};
    bot.executeSetPosCommand(command_data);
    EXPECT_EQ(bot.global_game_state.bot_position, utils::Position::EAST);
    EXPECT_EQ(bot.global_game_state.bot_partner_posititon, utils::Position::WEST);

    command_data = std::vector<std::string>{"SETPOS", "Player", "NORTH"};
    bot.executeSetPosCommand(command_data);
    EXPECT_EQ(bot.global_game_state.bot_position, utils::Position::EAST);
    EXPECT_EQ(bot.global_game_state.bot_partner_posititon, utils::Position::WEST);
}

TEST(BotTest, HandCommandShouldNotReactTest)
{
    auto client_ptr = std::make_unique<connection::FakeClient>();
    Bot bot("Bot_test", std::move(client_ptr));
    bot.global_game_state.bot_position = utils::Position::NORTH;

    bot.executeHandCommand(example_hand_command_south);
    for(int i = 0; i<4; i++)
    {
        EXPECT_EQ(bot.current_state.player_cards_points_sum[i], 0);
        for(int j = 0; j<52; j++)
        {
            EXPECT_EQ(bot.current_state.player_cards_points[i][j], 0);
        }
    }
}

TEST(BotTest, HandCommandShouldReactTest)
{
    auto client_ptr = std::make_unique<connection::FakeClient>();
    Bot bot("Bot_test", std::move(client_ptr));
    bot.global_game_state.bot_position = utils::Position::SOUTH;

    bot.executeHandCommand(example_hand_command_south);
    for(int i = 0; i<4; i++)
    {
        if(i == 2)
            continue;

        EXPECT_EQ(bot.current_state.player_cards_points_sum[i], 0);
        for(int j = 0; j<52; j++)
        {
            EXPECT_EQ(bot.current_state.player_cards_points[i][j], 0);
        }
    }
    EXPECT_EQ(bot.current_state.player_cards_points_sum[2], 13);
    for(int j = 0; j < 52; j++)
    {
        if (std::find(example_hand_int_values.begin(), example_hand_int_values.end(), j) != example_hand_int_values.end())
        {
            EXPECT_EQ(bot.current_state.player_cards_points[2][j], 1);
        } else
        {
            EXPECT_EQ(bot.current_state.player_cards_points[2][j], 0);
        }
    }
}