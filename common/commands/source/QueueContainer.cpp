#include <commands/MultiThreadCommandContainer.hpp>
#include <commands/QueueContainer.hpp>
#include <iostream>
#include <sstream>

void QueueContainer::pushCommand(std::string&& command)
{
    queue.emplace(command);
}

void QueueContainer::pushCommand(std::string& command)
{
    queue.emplace(std::move(command));
}

bool QueueContainer::popCommand(std::string& c)
{
    auto isEmpty = queue.empty();
    if (!isEmpty)
    {
        c = queue.front();
        queue.pop();
    }
    return !isEmpty;
}

bool QueueContainer::isEmpty()
{
    return queue.empty();
}

std::string QueueContainer::debugPrint()
{
    std::stringstream ss;
    ss << "Size of queue: " << queue.size()
        << "\t Top most element: " << queue.front() << std::endl;
    return ss.str();
}
