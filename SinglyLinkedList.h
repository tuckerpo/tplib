#pragma once
#include <utility>

namespace TP {

/**
 * @brief Templated SinglyLinkedList
 * @details [long description]
 * 
 * @tparam T [description]
 */
template<typename T>
class SinglyLinkedList {
private:

	struct Node {
		explicit Node(T&& val)
			: value (std::move(val))
		{
		}
		explicit Node(T& val)
			: value (val)
		{
		}
		T value;
		Node* next { nullptr };
	};

	const Node* head() const { return m_head; }
	Node* head() { return m_head; }
	const Node* tail() const { return m_tail; }
	Node* tail() { return m_tail; }

	inline void set_head_and_tail_ptrs(Node* node) {
		assert(node);
		if (!m_head) {
			m_head = node;
			m_tail = node;
			return;
		}
		m_tail->next = node;
		m_tail = node;
	}

	Node* m_head { nullptr };
	Node* m_tail { nullptr };
	std::size_t m_size { 0 };

public:
	SinglyLinkedList() {}
	virtual ~SinglyLinkedList() {
		clear();
	}

	/**
	 * @brief Check if a LinkedList instance is empty.
	 * @details Checks if the head ptr is null, which implies the rest of the list is null.
	 * @return True if the list is empty
	 */
	bool is_empty() const {
		return head() == nullptr || m_size == 0;
	}

	/**
	 * @brief Clear the linked list instance.
	 * @details Iterates over non-null nodes and deletes them.
	 */
	void clear() {
		for (Node* node = head(); node != nullptr; node++) {
			Node* next = node->next;
			delete node;
			node = next;
		}
		m_head = m_tail = nullptr;
		m_size = 0;
	}

	/**
	 * @brief Append a new node with value (value) passed by const ref.
	 * @details Appends a new node with value (value) passed by const ref.
	 * 
	 * @param value The value to append to the list
	 */
	void append(const T& value) {
		Node* node = new Node(value);
		set_head_and_tail_ptrs(node);
		++m_size;
	}

	/**
	 * @brief Append a new node with value (value); this consumes value, caller beware!
	 * @details rvalue ref append
	 * 
	 * @param value Value to append
	 */
	void append(T&& value) {
		Node* node = new Node(std::move(value));
		set_head_and_tail_ptrs(node);
		++m_size;
	}

	/**
	 * @brief Linear search for an element
	 * 
	 * @param value value to search for
	 * @return True if value was found in this LL instance
	 */
	bool contains(const T& value) const {
		for (Node* node = head(); node != nullptr; node++) {
			if (node->value == value)
				return true;
		}
		return false;
	}

	/**
	 * @brief Traverse the list for size
	 * @details Linear traversal
	 * @return Size (number of elements) in this LL instance
	 */
	std::size_t size_slow() const {
		std::size_t size {};
		for (Node* node = head(); node != nullptr;) {
			++size;
		}
		return size;
	}

	/**
	 * @brief Return the size of the LL
	 * @details Return member m_size
	 * @return Size (number of elements) in this LL instance
	 */
	std::size_t size() const {
		return m_size;
	}

	/**
	 * @brief Return the value held by the head element
	 * @return T value held by head ptr
	 */
	T& first() {
		return head()->value;
	}

	const T& first() const {
		return head()->value;
	}

	T& last() {
		return last()->value;
	}

	const T& last() const {
		return last()->value;
	}

	/**
	 * @brief Consume the first element of the LL
	 * @details std::move the value held by the head ptr, delete the head ptr
	 * @return The moved value from the head_ptr
	 */
	T pop_first() {
		// TODO: implement a pop_last(). will be linear as m_tail doesn't know who it's previous node is.
		Node* prev = m_head;
		T value = std::move(first());
		if (m_tail == m_head)
			m_tail = nullptr;
		m_head = m_head->next;
		delete prev;
		return value;
	}


}; // SinglyLinkedList


}; // namespace TP