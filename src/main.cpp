#include "List.h"
#include "StackAllocator.h"
#include "Vector.h"

#include <iostream>

int main()
{
    StackAllocator allocator;

    Vector vec(&allocator);
    vec.push_back(17);
    vec.push_back(4);
    vec.push_back(2);

    List list(&allocator);
    list.insert(42);
    list.insert(3);
    list.insert(5);
    list.insert(15);

    vec.push_back(13);

    std::cout << "vec:\n";
    for (auto val : vec) {
        std::cout << val << ' ';
    }
    std::cout << '\n';

    list.erase(list.end()->prev()->prev()); // erases 5

    std::cout << "list:\n";
    for (auto node = list.begin(); node != list.end(); node = node->next()) {
        std::cout << node->value() << ' ';
    }
    std::cout << '\n';

    return 0;
}