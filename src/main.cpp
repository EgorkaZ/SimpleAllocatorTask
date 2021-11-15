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
    vec.push_back(42);
    for (auto val : vec) {
        std::cout << val << '\n';
    }

    return 0;
}