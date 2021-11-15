#include "StackAllocator.h"
#include "Fwd.h"

#include <cstddef>
#include <iostream>

StackAllocator::~StackAllocator()
{
    auto * alloced = m_alloced_at;
    auto * end = alloced + Size;
    for (auto * alloced = m_alloced_at; alloced != m_alloced_at + Size; ++alloced) {
        if (*alloced != 0) {
            std::cout << "Leak of " << *alloced << " bytes at " << alloced << '\n';
        }
    }
}

Node * StackAllocator::alloc_node()
{
    // TODO
    return nullptr;
}

short * StackAllocator::alloc_short_arr(size_t size)
{
    auto to_alloc = size * sizeof(short);
    if (auto * found = find_size(to_alloc)) {
        size_t idx = found - m_buffer;
        m_alloced_at[idx] = to_alloc;
        bool * used = m_used + idx;
        bool * used_end = used + to_alloc;
        while (used != used_end) {
            *used++ = true;
        }
        return reinterpret_cast<short *>(found);
    }
    return nullptr;
}

short * StackAllocator::realloc_short_arr(size_t size, short *current)
{
    // TODO
    return nullptr;
}

void StackAllocator::free(void * node) noexcept
{
    // TODO
}

size_t StackAllocator::alloced_at(void * ptr) const noexcept
{
    auto idx = static_cast<const std::byte *>(ptr) - m_buffer;
    return m_alloced_at[idx];
}

std::byte * StackAllocator::find_size(size_t req_size) noexcept
{
    auto * end = m_used + Size - req_size;
    for (auto * ptr = m_used; ptr != end; ++ptr) {
        if (!*ptr) {
            bool found = true;
            auto * found_end = ptr + req_size;
            for (auto * used = ptr; used != found_end; ++used) {
                if (*used) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return m_buffer + (ptr - m_used);
            }
        }
    }
    return nullptr;
}
