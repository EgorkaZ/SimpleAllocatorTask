#include "List.h"
#include "StackAllocator.h"

List::~List() noexcept
{
    auto * node = begin();
    while (node != end()) {
        node = erase(node);
    }
}

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

    m_allocator->free(node);
    return next;
}
