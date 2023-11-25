#include <gtest/gtest.h>
#include <commands/CommandsUtils.hpp>
#include <string>

TEST(TestCommandUtils, CommandParseCorrectCommandTest)
{
    std::string command = "TEST ONE TWO THREE";
    std::vector<std::string> command_data;
    command = commands::parseCommand(command, command_data);

    std::vector<std::string> test_data{"TEST", "ONE", "TWO", "THREE"};
    ASSERT_EQ(command, "TEST");
    ASSERT_EQ(command_data, test_data);
}

TEST(TestCommandUtils, CommandParseSpaceEndedTest)
{
    std::string command = "SPACE AT THE END ";
    std::vector<std::string> command_data;
    command = commands::parseCommand(command, command_data);

    std::vector<std::string> test_data{"SPACE", "AT", "THE", "END"};
    ASSERT_EQ(command, "SPACE");
    ASSERT_EQ(command_data, test_data);
}
