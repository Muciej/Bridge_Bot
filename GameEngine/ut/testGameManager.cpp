#include <gtest/gtest.h>
#include <GameEngine/GameManager.hpp>
#include <vector>
#include <string>

TEST(TestGameManager, CommandParseCorrectCommandTest)
{
    Game::GameManager manager;
    std::string command = "TEST ONE TWO THREE";
    std::vector<std::string> command_data;
    command = manager.parseCommand(command, command_data);

    std::vector<std::string> test_data{"TEST", "ONE", "TWO", "THREE"};
    ASSERT_EQ(command, "TEST");
    ASSERT_EQ(command_data, test_data);
}

TEST(TestGameManager, CommandParseSpaceEndedTest)
{
    Game::GameManager manager;
    std::string command = "SPACE AT THE END ";
    std::vector<std::string> command_data;
    command = manager.parseCommand(command, command_data);

    std::vector<std::string> test_data{"SPACE", "AT", "THE", "END"};
    ASSERT_EQ(command, "SPACE");
    ASSERT_EQ(command_data, test_data);
}

TEST(TestGameManger, ShouldAddPlayerTest)
{
    Game::GameManager manager;
    manager.state = Game::GameState::IN_LOBBY;
    manager.connected_players[0] = true;
    manager.connected_players[1] = false;

    std::vector<std::string> test_data{"ADD_PLAYER", "JOHN", "BOT"};
    manager.addPlayer(test_data);

    Game::Player p("JOHN", Game::Position::EAST, true);
    ASSERT_EQ(manager.players[Game::Position::EAST], p);
    ASSERT_TRUE(manager.connected_players[1]);
}

TEST(TestGameManger, AddPlayerWrongCommandFormatTest)
{
    Game::GameManager manager;
    manager.state = Game::GameState::IN_LOBBY;
    manager.connected_players[0] = true;
    manager.connected_players[1] = false;

    std::vector<std::string> test_data{"ADD_PLAYER", "JOHN", "BOT", "GARBAGE"};
    ASSERT_ANY_THROW(manager.addPlayer(test_data));
}

TEST(TestGameManger, AddPlayerAllSlotsOccupiedTest)
{
    Game::GameManager manager;
    manager.state = Game::GameState::IN_LOBBY;
    manager.connected_players[0] = true;
    manager.connected_players[1] = true;
    manager.connected_players[2] = true;
    manager.connected_players[3] = true;

    std::vector<std::string> test_data{"ADD_PLAYER", "JOHN", "BOT"};
    ASSERT_ANY_THROW(manager.addPlayer(test_data));
}

TEST(TestGameManger, AddPlayerWrongStateTest)
{
    Game::GameManager manager;
    manager.state = Game::GameState::BIDDING;
    manager.connected_players[0] = false;

    std::vector<std::string> test_data{"ADD_PLAYER", "JOHN", "BOT"};
    ASSERT_ANY_THROW(manager.addPlayer(test_data));
}

TEST(TestGameManger, AddFourPlayersTest)
{
    Game::GameManager manager;

    std::vector<std::string> test_data1{"ADD_PLAYER", "JOHN", "PLAYER"};
    std::vector<std::string> test_data2{"ADD_PLAYER", "JACK", "BOT"};
    std::vector<std::string> test_data3{"ADD_PLAYER", "ADA", "PLAYER"};
    std::vector<std::string> test_data4{"ADD_PLAYER", "JULIA", "BOT"};
    manager.addPlayer(test_data1);
    manager.addPlayer(test_data2);
    manager.addPlayer(test_data3);
    manager.addPlayer(test_data4);

    ASSERT_TRUE(manager.connected_players[1] && manager.connected_players[2] && manager.connected_players[3] && manager.connected_players[4]);
    ASSERT_EQ(manager.players[Game::Position::NORTH], Game::Player("JOHN", Game::Position::NORTH, false));
    ASSERT_EQ(manager.players[Game::Position::EAST], Game::Player("JACK", Game::Position::EAST, true));
    ASSERT_EQ(manager.players[Game::Position::SOUTH], Game::Player("ADA", Game::Position::SOUTH, false));
    ASSERT_EQ(manager.players[Game::Position::WEST], Game::Player("JULIA", Game::Position::WEST, true));
}