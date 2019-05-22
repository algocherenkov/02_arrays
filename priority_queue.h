#pragma once
#include <memory>

template<typename T>
class PriorityQueue{
    struct Node{
        Node() = default;
        std::shared_ptr<T> data {nullptr};
        std::unique_ptr<Node> next {nullptr};
        int priority{0};
    };
public:
    PriorityQueue()
    {
        m_head = std::make_unique<Node>();
        m_tail = m_head.get();
    }

    void enqueue(const T& item, int priority)
    {
        std::shared_ptr<T> newData = std::make_shared<T>(item);
        std::unique_ptr<Node> newVertex(std::make_unique<Node>());

        m_tail->data = newData;
        m_tail->priority = priority;

        Node* const newTail = newVertex.get();

        m_tail->next = std::move(newVertex);
        m_tail = newTail;
    }

    std::shared_ptr<T> dequeue()
    {
        if(m_head.get() != m_tail)
        {
            Node* nodeBeforePrior = m_head.get();
            Node* iter = m_head.get();
            std::shared_ptr<T> data;
            bool nodeChanged = false;

            while(iter)
            {
                int max = iter->priority;
                if(iter->next && max < iter->next->priority)
                {
                    nodeBeforePrior = iter;
                    nodeChanged = true;
                }
                iter = iter->next.get();
            }

            if(nodeBeforePrior->next->data)
                data = nodeBeforePrior->next->data;
            else
                data = nodeBeforePrior->data;

            if(!nodeChanged)
            {
                m_head = std::move(m_head->next);
            }
            else
            {
                nodeBeforePrior->next = std::move(nodeBeforePrior->next->next);
            }

            return data;
        }
        else
            return nullptr;
    }
private:
    std::unique_ptr<Node> m_head;
    Node* m_tail{nullptr};
};
