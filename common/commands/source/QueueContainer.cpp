#include <MultiThreadCommandContainer.hpp>
#include <QueueContainer.hpp>

void QueueContainer::pushCommand(std::string&& command) override
{
    queue.emplace(command);
}

void QueueContainer::pushCommand(std::string& command) override
{
    queue.emplace(std::move(command));
}

bool QueueContainer::popCommand(std::string& c) override
{
    auto isEmpty = queue.empty();
    if (!isEmpty)
    {
        c = queue.front();
        queue.pop();
    }
    return !isEmpty;
}

bool QueueContainer::isEmpty() override
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
