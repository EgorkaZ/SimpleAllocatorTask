#pragma once

#include "Fwd.h"

class Node
{
    friend class List;

public:
    Node (int val, Node * prev = nullptr, Node * next = nullptr)
        : m_prev(prev)
        , m_next(next)
        , m_value(val)
    {}

    Node * next() noexcept { return m_next; }
    Node * prev() noexcept { return m_prev; }

    const Node * next() const noexcept { return m_next; }
    const Node * prev() const noexcept { return m_prev; }

private:
    Node * m_prev = nullptr;
    Node * m_next = nullptr;
    int m_value = 0;
};

class List
{
public:
    List (StackAllocator * allocator)
        : m_node(0, &m_node, &m_node)
        , m_allocator(allocator)
    {}

    ~List() noexcept;

    /**
     * @brief Inserts a new value
     *
     * @param val inserted value
     * @return inserted Node
     */
    Node * insert(int val);

    /**
     * @brief Deletes specified node
     *
     * @param node to delete
     * @return next() of the deleted node
     */
    Node * erase(Node * node);

    bool empty() const noexcept { return m_node.m_next == m_node.m_prev; }

    Node * begin() noexcept { return m_node.m_next;  }
    Node * end() noexcept { return &m_node; }

private:
    Node m_node;
    StackAllocator * m_allocator;
};
