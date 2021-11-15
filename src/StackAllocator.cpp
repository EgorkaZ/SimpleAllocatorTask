#include "Fwd.h"
#include "List.h"
#include "StackAllocator.h"

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
    const size_t to_alloc = sizeof(Node);
    if (auto * found = find_size(sizeof(Node))) {
        alloc_at(found, to_alloc);
        return reinterpret_cast<Node *>(found);
    }
    return nullptr;
}

short * StackAllocator::alloc_short_arr(size_t size)
{
    auto to_alloc = size * sizeof(short);
    if (auto * found = find_size(to_alloc)) {
        alloc_at(found, to_alloc);
        return reinterpret_cast<short *>(found);
    }
    return nullptr;
}

short * StackAllocator::realloc_short_arr(size_t size, short * current)
{
    size_t to_alloc = size * sizeof(short);

    if (current != nullptr) {
        size_t alloced = alloced_at(current);
        if (to_alloc > alloced) {
            std::byte * from = reinterpret_cast<std::byte *>(current);
            if (auto * res = find_size_from(to_alloc - alloced, from + alloced)) {
                alloc_at(from, to_alloc);
                return current;
            }
        }
    }
    return alloc_short_arr(size);
}

void StackAllocator::free(void * node) noexcept
{
    auto * byte_ptr = static_cast<std::byte *>(node);
    auto idx = byte_ptr - m_buffer;
    auto alloced = m_alloced_at[idx];
    m_alloced_at[idx] = 0;

    auto * used_end = m_used + idx + alloced;
    for (auto * used = m_used + idx; used != used_end; ++used) {
        *used = false;
    }
}

void StackAllocator::alloc_at(std::byte * ptr, size_t to_alloc)
{
    size_t idx = ptr - m_buffer;
    m_alloced_at[idx] = to_alloc;
    bool * used_end = m_used + idx + to_alloc;
    for (bool * used = m_used + idx; used != used_end; ++used) {
        *used = true;
    }
}

size_t StackAllocator::alloced_at(void * ptr) const noexcept
{
    auto idx = static_cast<const std::byte *>(ptr) - m_buffer;
    return m_alloced_at[idx];
}

std::byte * StackAllocator::find_size_from(size_t req_size, const std::byte * from) noexcept
{
    auto * end = m_used + Size - req_size;
    for (auto * ptr = m_used + (from - m_buffer); ptr != end; ++ptr) {
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
