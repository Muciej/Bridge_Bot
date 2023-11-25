#include <gtest/gtest.h>
#include <GameEngine/GameManager.hpp>
#include <utils/Player.hpp>
#include <vector>
#include <string>

TEST(TestGameManger, ShouldAddPlayerTest)
{
    game::GameManager manager;
    manager.state = game::GameState::IN_LOBBY;
    manager.connected_players[0] = true;
    manager.connected_players[1] = false;

    std::vector<std::string> test_data{"ADD_PLAYER", "JOHN", "BOT"};
    manager.addPlayer(test_data);

    utils::Player p("JOHN", utils::Position::EAST, true);
    ASSERT_EQ(manager.players[utils::Position::EAST], p);
    ASSERT_TRUE(manager.connected_players[1]);
    
}

TEST(TestGameManger, AddPlayerWrongCommandFormatTest)
{
    game::GameManager manager;
    manager.state = game::GameState::IN_LOBBY;
    manager.connected_players[0] = true;
    manager.connected_players[1] = false;

    std::vector<std::string> test_data{"ADD_PLAYER", "JOHN", "BOT", "GARBAGE"};
    ASSERT_ANY_THROW(manager.addPlayer(test_data));
}

TEST(TestGameManger, AddPlayerAllSlotsOccupiedTest)
{
    game::GameManager manager;
    manager.state = game::GameState::IN_LOBBY;
    manager.connected_players[0] = true;
    manager.connected_players[1] = true;
    manager.connected_players[2] = true;
    manager.connected_players[3] = true;

    std::vector<std::string> test_data{"ADD_PLAYER", "JOHN", "BOT"};
    ASSERT_ANY_THROW(manager.addPlayer(test_data));
}

TEST(TestGameManger, AddPlayerWrongStateTest)
{
    game::GameManager manager;
    manager.state = game::GameState::BIDDING;
    manager.connected_players[0] = false;

    std::vector<std::string> test_data{"ADD_PLAYER", "JOHN", "BOT"};
    ASSERT_ANY_THROW(manager.addPlayer(test_data));
}

TEST(TestGameManger, AddFourPlayersTest)
{
    game::GameManager manager;

    std::vector<std::string> test_data1{"ADD_PLAYER", "JOHN", "PLAYER"};
    std::vector<std::string> test_data2{"ADD_PLAYER", "JACK", "BOT"};
    std::vector<std::string> test_data3{"ADD_PLAYER", "ADA", "PLAYER"};
    std::vector<std::string> test_data4{"ADD_PLAYER", "JULIA", "BOT"};
    manager.addPlayer(test_data1);
    manager.addPlayer(test_data2);
    manager.addPlayer(test_data3);
    manager.addPlayer(test_data4);

    ASSERT_TRUE(manager.connected_players[1] && manager.connected_players[2] && manager.connected_players[3] && manager.connected_players[4]);
    ASSERT_EQ(manager.players[utils::Position::NORTH], utils::Player("JOHN", utils::Position::NORTH, false));
    ASSERT_EQ(manager.players[utils::Position::EAST], utils::Player("JACK", utils::Position::EAST, true));
    ASSERT_EQ(manager.players[utils::Position::SOUTH], utils::Player("ADA", utils::Position::SOUTH, false));
    ASSERT_EQ(manager.players[utils::Position::WEST], utils::Player("JULIA", utils::Position::WEST, true));
}