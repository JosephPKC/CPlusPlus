//
// Created by Joe on 6/28/2017.
//

#ifndef C_LINKEDLIST_H
#define C_LINKEDLIST_H
#include <iostream>

namespace List {
    enum Error {
        UNEXPECTED_ERROR,
        OK,
        NODE_NOT_IN_LIST,
	    INDEX_OUT_OF_RANGE,
	    EMPTY
    };

    /* Whatever T is should have an overloaded assignment operator (that copies the values to the new) and a default constructor */


    template <typename T>
    class LinkedList {
	    struct Node {
		    T _element;
		    Node* _next;

		    Node(const T& element = T()) {
			    _element = element;
			    _next = nullptr;
		    }

		    Node(const Node& other) {
			    _element = other._element;
			    if(other._next) {
				    _next = new Node(other._next);
			    }
			    else {
				    _next = nullptr;
			    }
		    }

		    friend std::ostream& operator <<(std::ostream& out, const Node& other) {
			    out << other._element;
			    if(other._next) {
				    out << ", " << *other._next;
			    }
			    else {
				    out << "||";
			    }
			    return out;
		    }
	    };

        Node* _head;
	    Node* _tail;
        std::size_t _size;

        bool IsInList(Node* node);
        Node* Next(Node* node) const;
        Node* Previous(Node* node);
        Node* Previous(std::size_t index);
        std::size_t FindSize(Node* start);
		Node* FindLast();
	    Node* FromIndex(std::size_t index) const;
	    LinkedList(Node* head);

        public:
        // Constructors
        LinkedList();
        LinkedList(const T& element);
        LinkedList(T array[], std::size_t size);

        // The Big Three
        LinkedList(const LinkedList<T>& other);
        LinkedList<T>& operator =(const LinkedList<T>& other);
        ~LinkedList();

        // Insert/Remove
        LinkedList<T>& InsertBefore(const T& element, std::size_t index);
	    LinkedList<T>& InsertAfter(const T& element, std::size_t index);
	    LinkedList<T>& InsertFront(const T& element);
	    LinkedList<T>& InsertEnd(const T& element);
	    LinkedList<T>& RemoveAt(std::size_t index);
	    LinkedList<T>& RemoveFront();
	    LinkedList<T>& RemoveEnd();
	    LinkedList<T>& Append(const LinkedList<T>& other);

		// Access/Info
        T At(std::size_t index) const;
        T& At(std::size_t index);
        T Front() const;
        T End() const;
        T operator[](std::size_t index) const;
        T& operator[](std::size_t index);
	    std::size_t Size() const;
	    bool IsEmpty() const;

	    // Representations
        std::string ToString() const;
        T* ToArray() const;

	    // Misc
        LinkedList<T> Reverse();
        LinkedList<T> SubList(std::size_t from, std::size_t to) const;
        void Swap(std::size_t index1, std::size_t index2);

        /* Debug method */
        void __print__() const {
	        if(!_head) {
		        std::cout << "{}" << std::endl;
	        }
	        else {
		        Node* walker = _head;
		        std::cout << "{ ";
		        while (walker->_next) {
			        std::cout << walker->_element << ", ";
			        walker = Next(walker);
		        }
		        std::cout << walker->_element << " }" << std::endl;
	        }

        }
    };

    /* *************** DEFINITIONS *************** */
    // Some Notes:
    // Template class implementations must be implemented in the header file
    // Everything pertaining to the class must have a template argument (like Scope Resolution, etc)
	// Node is a nested class. It makes use of Linked List's template
	// To use this nested class, take off the <T> from all Nodes
	// Make sure to use scope resolution outside of the class for the Node
	// Add typename when returning a Node from a function

    template <typename T>
    /* O(n), n is size of list */
    bool LinkedList<T>::IsInList(Node* node) {
        Node* walker = _head;
        while (walker) {
            if (walker->IsExact(node)) {
                return true;
            }
            ++walker;
        }
        return false;
    }

    template <typename T>
    typename LinkedList<T>::Node* LinkedList<T>::Next(Node* node) const {
        return node->_next;
    }

    template <typename T>
    /* O(1) + O(n) */
    typename LinkedList<T>::Node* LinkedList<T>::Previous(Node* node) {
        if (_head == node) // Node is the head; No previous
            return nullptr;

        Node* walker = _head;
        while (walker->_next) {  // Check one ahead.
            if (walker->_next == node) //Is the node that's one ahead the same as our argument?
                return walker; //Return the one right before that
            walker = Next(walker);
        }
        throw NODE_NOT_IN_LIST;
    }

    template <typename T>
    /* O(1) + O(n) */
    typename LinkedList<T>::Node* LinkedList<T>::Previous(std::size_t index) {
        // Essentially the same as Previous(Node*), except use indices
        if (index >= Size()) { // Preliminary check to make sure the index is not out of bounds
            throw NODE_NOT_IN_LIST;
        }

        if (index == 0) // 0 index is the head always
            return nullptr;

        int count = 1;
        Node* walker = _head;
        while (walker->_next) {
            if (count == index)
                return walker;

            walker = Next(walker);
            ++count;
        }
        throw UNEXPECTED_ERROR; // Theoretically, it should never reach this point, unless something unexpected happens.
    }

    template <typename T>
    /* O(n) */
    std::size_t LinkedList<T>::FindSize(Node* start) {
        Node* walker = start;
        std::size_t size = 0;
        while (walker) {
            walker = Next(walker);
            ++size;
        }
        return size;
    }

	template <typename T>
	/* O(n) */
	typename LinkedList<T>::Node* LinkedList<T>::FindLast() {
		Node* walker = _head;
		while(walker->_next) {
			walker = Next(walker);
		}
		return walker;
	}

	template <typename T>
	typename LinkedList<T>::Node* LinkedList<T>::FromIndex(std::size_t index) const {
		if(index >= _size) {
			throw INDEX_OUT_OF_RANGE;
		}
		std::size_t count = 0;
		Node* walker = _head;
		while(count < index && walker) {
			++count;
			walker = Next(walker);
		}
		return walker;
	}

	template <typename T>
	LinkedList<T>::LinkedList(Node* head) {
		_head = head;
		_tail = FindLast();
		_size = FindSize(_head);
	}

    template <typename T>
    LinkedList<T>::LinkedList() {
        _head = nullptr; // Create an empty list
        _size = 0;
	    _tail = nullptr;
    }

    template <typename T>
    LinkedList<T>::LinkedList(const T& element) {
        Node* head = new Node(element);
        _head = head;
        _size = 1;
	    _tail = _head;
    }

    template <typename T>
    /* O(1) + O(n) */
    LinkedList<T>::LinkedList(T array[], std::size_t size) {
        if (size == 0) {// If the array is empty, just create an empty list
	        _head = nullptr;
	        _tail = nullptr;
	        _size = 0;
        }
	    else {
	        Node* head = new Node(array[0]);
	        _head = head;

	        // Go through every element in the array except the first and create a node for it and place it at the end of the previous nodes.
	        Node* walker = _head;
	        for (int i = 1; i < size; ++i, walker = Next(walker)) {
		        Node* temp = new Node(array[i]);
		        walker->_next = temp;
	        }
	        _tail = walker;
	        _size = size;
        }
    }

    template <typename T>
    LinkedList<T>::LinkedList(const LinkedList<T>& other) {
	    if(!other._head) {
		    _head = nullptr;
		    _tail = nullptr;
		    _size = 0;
	    }
	    else {
		    _head = new Node(other._head->_element);

		    Node* walkerOther = other._head->_next;
		    Node* walker = _head;

		    while(walkerOther) {
			    walker->_next = new Node(walkerOther->_element);
			    walker = Next(walker);
			    walkerOther = Next(walkerOther);
		    }
		    _tail = walker;
	    }
    }

    template <typename T>
    LinkedList<T>& LinkedList<T>::operator =(const LinkedList<T>& other) {
	    if(!other._head) {
		    _head = nullptr;
		    _tail = nullptr;
		    _size = 0;
	    }
	    else {
		    _head = new Node(other._head->_element);

		    Node* walkerOther = other._head->_next;
		    Node* walker = _head;

		    while(walkerOther) {
			    walker->_next = new Node(walkerOther->_element);
			    walker = Next(walker);
			    walkerOther = Next(walkerOther);
		    }
		    _tail = walker;
	    }
	    return *this;
    }

    template <typename T>
    LinkedList<T>::~LinkedList() {
	    Node* walker = _head;
	    while(walker) {
		    Node* temp = walker;
		    walker = Next(walker);
		    delete temp;
	    }
	    delete walker;
    }

    template <typename T>
    LinkedList<T>& LinkedList<T>::InsertBefore(const T& element, std::size_t index) {
	    try {
		    if(!_head) {
			    _head = new Node(element);
			    ++_size;
			    _tail = _head;
			    return *this;
		    }
		    Node* newNode = new Node(element);
		    if(index == 0) {
			    newNode->_next = _head;
			    _head = newNode;
		    }
		    else {
			    Node* after = FromIndex(index);
			    Node* before = FromIndex(index - 1);
			    before->_next = newNode;
			    newNode->_next = after;
		    }
			++_size;
		    return *this;
	    }
		catch(Error e) {
			throw e;
		}

    }

    template <typename T>
    LinkedList<T>& LinkedList<T>::InsertAfter(const T& element, std::size_t index) {
	    try {
		    if(!_head) {
			    _head = new Node(element);
			    ++_size;
			    _tail = _head;
			    return *this;
		    }
			Node* newNode = new Node(element);
		    if(index == Size() - 1) {
			    Node* before = _tail;
			    before->_next = newNode;
			    _tail = newNode;
		    }
		    else {
			    Node* after = FromIndex(index + 1);
			    Node* before = FromIndex(index);
			    before->_next = newNode;
			    newNode->_next = after;
		    }
		    ++_size;
		    return *this;
	    }
	    catch(Error e) {
		    throw e;
	    }
    }

    template <typename T>
    LinkedList<T>& LinkedList<T>::InsertFront(const T& element) {
	    try {
		    return InsertBefore(element, 0);
	    }
	    catch(Error e) {
		    throw e;
	    }
    }

    template <typename T>
    LinkedList<T>& LinkedList<T>::InsertEnd(const T& element) {
	    try {
		    return InsertAfter(element, Size() - 1);
	    }
	    catch(Error e) {
		    throw e;
	    }
    }

    template <typename T>
    LinkedList<T>& LinkedList<T>::RemoveAt(std::size_t index) {
	    try {
		    if(!_head) {
			    return *this;
		    }
		    Node* at;
		    if(index == 0) {
			    at = _head;
			    _head = _head->_next;
		    }
		    else {
			    at = FromIndex(index);
			    Node* before = Previous(at);
			    Node* after = at->_next;
			    before->_next = after;
		    }
		    --_size;
		    at->_next = nullptr;
		    delete at;
		    return *this;
	    }
	    catch(Error e) {
		    throw e;
	    }
    }

    template <typename T>
    LinkedList<T>& LinkedList<T>::RemoveFront() {
	    try {
		    return RemoveAt(0);
	    }
	    catch(Error e) {
		    throw e;
	    }
    }

    template <typename T>
    LinkedList<T>& LinkedList<T>::RemoveEnd() {
	    try {
		    return RemoveAt(_size - 1);
	    }
	    catch(Error e) {
		    throw e;
	    }
    }

	template <typename T>
	LinkedList<T>& LinkedList<T>::Append(const LinkedList<T>& other) {
		_tail->_next = other._head;
		_tail = other._tail;
		_size += other._size;
		return *this;
	}

    template <typename T>
    T LinkedList<T>::At(std::size_t index) const {
	    try {
		    return FromIndex(index)->_element;
	    }
	    catch(Error e) {
			throw e;
	    }
    }

    template <typename T>
    T& LinkedList<T>::At(std::size_t index) {
	    try {
		    return FromIndex(index)->_element;
	    }
	    catch(Error e) {
		    throw e;
	    }
    }

    template <typename T>
    T LinkedList<T>::Front() const {
	    return _head->_element;
    }

    template <typename T>
    T LinkedList<T>::End() const {
	    return _tail->_element;
    }

    template <typename T>
    T LinkedList<T>::operator [](std::size_t index) const {
	    try {
		    return At(index);
	    }
	    catch(Error e) {
		    throw e;
	    }
    }

    template <typename T>
    T& LinkedList<T>::operator [](std::size_t index) {
	    try {
		    return At(index);
	    }
	    catch(Error e) {
		    throw e;
	    }
    }

    template <typename T>
    std::string LinkedList<T>::ToString() const {
	    Node* walker = _head;
	    std::string stringRepr = "{";

	    while(walker->_next) {
		    stringRepr += std::to_string(walker->_element) + ", ";
		    walker = Next(walker);
	    }
		stringRepr += std::to_string(walker->_element) + "}";
	    return stringRepr;
    }

    template <typename T>
    std::size_t LinkedList<T>::Size() const {
        return _size;
    }

    template <typename T>
    bool LinkedList<T>::IsEmpty() const {
	    return !_head;
    }

    template <typename T>
    T* LinkedList<T>::ToArray() const {
	    Node* walker = _head;
	    T* array = new T[_size];
	    for(std::size_t i = 0; i < _size; ++i, walker = Next(walker)) {
		    array[i] = walker->_element;
	    }
	    return array;
    }

    template <typename T>
    LinkedList<T> LinkedList<T>::Reverse() {
	    if(!_head) {
		    return LinkedList<T>();
	    }
	    else {
		    LinkedList<T> reversed(*this);
		    Node* walker = reversed._head;
		    Node* rWalker = reversed._tail;
		    while(walker != rWalker && rWalker->_next != walker) {
			    T temp = walker->_element;
			    walker->_element = rWalker->_element;
			    rWalker->_element = temp;
			    walker = reversed.Next(walker);
			    rWalker = reversed.Previous(rWalker);
		    }
		    return reversed;
	    }
    }

    template <typename T>
    LinkedList<T> LinkedList<T>::SubList(std::size_t from, std::size_t to) const {
	    try {
		    Node* fromNode = FromIndex(from);
		    Node* toNode = FromIndex(to);
		    Node* subHead = new Node(fromNode->_element);
		    Node* subWalker = subHead;
		    fromNode = Next(fromNode);
		    while(toNode->_next != fromNode) {
			    subWalker->_next = new Node(fromNode->_element);
			    subWalker = subWalker->_next;
			    fromNode = Next(fromNode);
		    }
		    return LinkedList<T>(subHead);
	    }
	    catch(Error e) {
		    throw e;
	    }
    }

    template <typename T>
    void LinkedList<T>::Swap(std::size_t index1, std::size_t index2) {
	    try {
		    Node* oneNode = FromIndex(index1);
		    Node* twoNode = FromIndex(index2);
		    T temp = oneNode->_element;
		    oneNode->_element = twoNode->_element;
		    twoNode->_element = temp;
	    }
	    catch(Error e) {
		    throw e;
	    }
    }
}
#endif //C_LINKEDLIST_H
