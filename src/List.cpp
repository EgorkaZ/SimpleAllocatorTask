#include "List.h"
#include "StackAllocator.h"

Node * List::insert(int val)
{
    auto * new_node = m_allocator->alloc_node();
    if (!new_node) {
        return nullptr;
    }

    *new_node = Node(val, m_node.m_prev, &m_node);

    m_node.prev()->m_next = new_node;
    m_node.m_prev = new_node;
    return new_node;
}

Node * List::erase(Node * node)
{
    auto * next = node->next();

    node->prev()->m_next = next;
    next->m_prev = node->prev();

    return next;
}
