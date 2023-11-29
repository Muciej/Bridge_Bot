#include <iostream>
#include <list>

void printList(const std::list<int>& list)
{
    for(const auto& i : list)
    {
        std::cout << i << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    std::list<int> list;
    for(int i = 0; i<10; i++)
    {
        list.push_back(i);
    }
    printList(list);

    for(auto it = list.begin(); it != list.end(); it++)
    {
        if(*it == 9)
        {
            it = list.erase(it);
        }
    }

    printList(list);

    return 0;
}