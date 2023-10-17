#include <gtest/gtest.h>
#include <commands/QueueContainer.hpp>
#include <string>

TEST(QueueContainerTests, EmptyQueue)
{
    QueueContainer conatiner;
    ASSERT_EQ(conatiner.isEmpty(), true);
    std::string out;
    ASSERT_EQ(conatiner.popCommand(out), false);
}

TEST(QueueContainerTests, AddingElemToQueue)
{
    QueueContainer conatiner;
    conatiner.pushCommand("Test 1");
    conatiner.pushCommand("Test 2");
    ASSERT_EQ(conatiner.isEmpty(), false);
}

TEST(QueueContainerTests, PoppingElems)
{
    QueueContainer conatiner;
    std::string out;

    conatiner.pushCommand("Test 1");
    conatiner.pushCommand("Test 2");
    ASSERT_EQ(conatiner.popCommand(out), true);
    ASSERT_EQ(out, "Test 1");
    ASSERT_EQ(conatiner.popCommand(out), true);
    ASSERT_EQ(out, "Test 2");
    ASSERT_EQ(conatiner.popCommand(out), false);
}

TEST(QueueContainerTests, DebugPrint)
{
    QueueContainer conatiner;
    conatiner.pushCommand("Test 1");
    conatiner.pushCommand("Test 2");

    ASSERT_EQ(conatiner.debugPrint(), "Size of queue: 2\t Top most element: Test 1\n");
}
