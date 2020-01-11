#pragma once
#include <utility>
#include <cstddef>

namespace TP {

template<typename T>
class SinglyLinkedList {
public:
    SinglyLinkedList() {}
    virtual ~SinglyLinkedList() {
        clear();
    }

    void clear() {
        for (Node* node = m_Head; node;) {
           Node* next = node->next;
           delete node;
           node = next;
        }
        m_Head = nullptr;
        m_Tail = nullptr;
    }

    std::size_t size_linear() const {
        std::size_t size;
        for (Node* node = m_Head; node; node = node->next) {
            ++size;
        }
        return size;
    }

    std::size_t size() const {
        return m_Size;
    }

    bool is_empty() {
        return m_Size > 0;
    }

    T& first() {
        return head()->value;
    }

    const T& first() const {
        return head()->value;
    }

    T& last() {
        return tail()->value;
    }

    const T& last() const {
        return tail()->value;
    }

    T pop_first() {
        Node* old_head = m_Head;
        T value = std::move(first());
        if (m_Tail == m_Head) {
            m_Tail = nullptr;
        }
        m_Head = m_Head->next;
        delete old_head;
        return value;
    }

    void append(const T& value) {
        Node* node = new Node(value);
        if (!m_Head) {
            m_Head = node;
            m_Tail = node;
            return;
        }
        m_Tail->next = node;
        m_Tail = node;
    }

    void append(T&& value) {
        Node* node = new Node(std::move(value));
        if (!m_Head) {
            m_Head = node;
            m_Tail = node;
            return;
        }
        m_Tail->next = node;
        m_Tail = node;
    }

    bool contains(const T& value) {
        for (Node* node = m_Head; node; node = node->next) {
            if (node->data == value) {
                return true;
            }
        }
        return false;
    }

    template<typename FinderFunc>
    bool find(FinderFunc finderfn) {
        for (Node* node = m_Head; node; node = node->next) {
            if (finderfn(node->data)) {
                return true;
            }
        }
        return false;
    }

    template<typename Func>
    void for_each_value(Func fn) {
        for (Node* node = m_Head; node; node = node->next) {
            fn(node->data);
        }
    }

    template<typename Func>
    void for_each_node(Func fn) {
        for (Node *node = m_Head; node; node = node->next) {
            fn(node);
        }
    }

private:
    struct Node {
        explicit Node(T& val)
            : data (val) {}
        explicit Node(T&& val)
            : data (std::move(val)) {}
        T data;
        Node *next {nullptr};
    };

    Node* m_Head {nullptr};
    Node* m_Tail {nullptr};
    const Node* head() const { return m_Head; }
    Node* head() { return m_Head; }
    const Node* tail() const { return m_Tail; }
    Node* tail() { return m_Tail; }
    std::size_t m_Size { 0 };
};

}; // namespace TP
