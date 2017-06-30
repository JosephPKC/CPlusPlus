//
// Created by Joe on 6/29/2017.
//

#ifndef C_CIRCULARLINKEDLIST_H
#define C_CIRCULARLINKEDLIST_H
#include <iostream>
#include "LinkedList.h"

namespace List {
	/* This will only contain the standard methods */
	template <typename T>
	class CircularLinkedList {
		struct Node {
			T _item;
			Node* _next;
			Node* _prev;

			// Constructor. Sets next and prev to null.
			Node(const T& item)
					: _item(item), _next(nullptr), _prev(nullptr) {};
		};

		Node* _ref; //Instead of a head, this is a reference point to act as the "start". Since this is circular, there is no start or end.
		std::size_t _size;

		std::size_t Count() const;
		void MakeNew(const T& item);
		Node* FromIndex(std::size_t index) const;
		CircularLinkedList(Node* node);
		public:
		CircularLinkedList();
		CircularLinkedList(const T& item);
		CircularLinkedList(T array[], std::size_t size);
		CircularLinkedList(const CircularLinkedList<T>& other);
		CircularLinkedList<T>& operator =(const CircularLinkedList<T>& other);
		~CircularLinkedList();

		CircularLinkedList<T>& Insert(const T& item, std::size_t index, bool a = true);
		CircularLinkedList<T>& Remove(std::size_t index);

		T operator [](std::size_t index) const;
		T& operator [](std::size_t index);

		std::size_t Size() const;
		bool IsEmpty() const;
		friend std::ostream& operator <<(std::ostream& out, const CircularLinkedList<T>& other);
	};

	template <typename T>
	std::size_t CircularLinkedList<T>::Count() const {
		//Begin at ref. Then increment until you hit ref again
		std::size_t size = 0;
		Node* walker = _ref;
		while(walker != _ref) {
			++size;
		}
		return size;
	}

	template <typename T>
	void CircularLinkedList<T>::MakeNew(const T& item) {
		_ref = new Node(item);
		_size = 1;
	}

	template <typename T>
	typename CircularLinkedList<T>::Node* CircularLinkedList<T>::FromIndex(std::size_t index) const {
		std::size_t count = 0;
		index = index % _size; //Mod the index so it is 0 to _size - 1
		Node* walker = _ref;
		bool backwards = index > _size / 2; //Figure out which direction we should go from ref.
		if(backwards)
			index = _size - index - 1; //Change to the "reverse" index
		do {
			if(index == count)
				return walker;
			walker = backwards ? walker->_prev : walker->_next;
			++count;
		} while(walker != _ref);
		return nullptr;
	}

	template <typename T>
	CircularLinkedList<T>::CircularLinkedList(Node* node) {
		_ref = node;
		_size = Count();
	}

	template <typename T>
	CircularLinkedList<T>::CircularLinkedList() {
		_ref = nullptr;
		_size = 0;
	}

	template <typename T>
	CircularLinkedList<T>::CircularLinkedList(const T& item) {
		_ref = new Node(item);
		_size = 1;
	}

	template <typename T>
	CircularLinkedList<T>::CircularLinkedList(T array[], std::size_t size) {
		_size = 0;
		if(_size == 0)
			_ref = nullptr;
		else {
			_ref = new Node(array[0]);
			Node* walker = _ref;
			for(int i = 1; i < _size; ++i) {
				Node* temp = new Node(array[i]);
				temp->_prev = walker;
				walker->_next = temp;
				walker = walker->_next;
			}
			walker->_next = _ref;
			_ref->_prev = walker;
		}
	}

	template <typename T>
	CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& other) {
		if(other.IsEmpty()) {
			_ref = nullptr;
			_size = 0;
		}
		else {
			_size = other._size;
			_ref = new Node(other._ref->_item);
			Node* walker = _ref;
			Node* oWalker = other._ref->_item;
			while(oWalker) {
				Node* temp = new Node(oWalker->_item);
				temp->_prev = walker;
				walker->_next = temp;
				walker = walker->_next;
				oWalker = oWalker->_next;
			}
			walker->_next = _ref;
			_ref->_prev = walker;
		}
	}

	template <typename T>
	CircularLinkedList<T>& CircularLinkedList<T>::operator =(const CircularLinkedList<T>& other) {
		if(other.IsEmpty()) {
			_ref = nullptr;
			_size = 0;
		}
		else {
			_size = other._size;
			_ref = new Node(other._ref->_item);
			Node* walker = _ref;
			Node* oWalker = other._ref->_item;
			while(oWalker) {
				Node* temp = new Node(oWalker->_item);
				temp->_prev = walker;
				walker->_next = temp;
				walker = walker->_next;
				oWalker = oWalker->_next;
			}
			walker->_next = _ref;
			_ref->_prev = walker;
		}
		return *this;
	}

	template <typename T>
	CircularLinkedList<T>::~CircularLinkedList() {
		//Set the "last" one to end
		_ref->_prev->_next = nullptr;
		_ref->_prev = nullptr;
		while(_ref) {
			Node* temp = _ref;
			_ref = _ref->_next;
			delete _ref;
		}
	}

	template <typename T>
	CircularLinkedList<T>& CircularLinkedList<T>::Insert(const T& item, std::size_t index, bool a = true) {
		//Insert After
		if(index >= _size) {
			return *this;
		}
		if(!_ref) {
			MakeNew(item);
			return*this;
		}
		Node* newNode = new Node(item);
		if(index == 0 && !a) {
			_ref->_prev = newNode;
			newNode->_next = _ref;
			_ref = newNode;
		}
		if(index != 0){
			Node* after = a ? FromIndex(index + 1) : FromIndex(index);
			Node* before = a ? FromIndex(index) : FromIndex(index - 1);

			before->_next = newNode;
			newNode->_prev = before;
			newNode->_next = after;
			after->_prev = newNode;
		}
		++_size;
		return *this;
	}

	template <typename T>
	CircularLinkedList<T>& CircularLinkedList<T>::Remove(std::size_t index) {
		if(!_ref)
			return *this;
		if(index >= _size)
			return*this;

		Node* deleteNode;
		if(index == 0) {
			deleteNode = _ref;
			_ref->_prev->_next = _ref->_next;
			_ref->_next->_prev = _ref->_prev;
			_ref = _ref->_next;
		}
		else {
			deleteNode = FromIndex(index);
			Node* before = deleteNode->_prev;
			Node* after = deleteNode->_next;
			before->_next = after;
			after->_prev = before;
		}

		--_size;
		deleteNode->_next = nullptr;
		deleteNode->_prev = nullptr;
		delete deleteNode;
		return *this;
	}

	template <typename T>
	T CircularLinkedList<T>::operator [](std::size_t index) const {
		Node* here = FromIndex(index);
		if(!here)
			throw Error::INDEX_OUT_OF_RANGE;
		return here->_item;
	}

	template <typename T>
	T& CircularLinkedList<T>::operator [](std::size_t index) {
		Node* here = FromIndex(index);
		if(!here)
			throw Error::INDEX_OUT_OF_RANGE;
		return here->_item;
	}

	template <typename T>
	std::size_t CircularLinkedList<T>::Size() const {
		return _size;
	}

	template <typename T>
	bool CircularLinkedList<T>::IsEmpty() const {
		return !_ref;
	}

	template <typename T>
	std::ostream& operator <<(std::ostream& out, const CircularLinkedList<T>& other) {
		if(!_ref) {
			out << "{}";
			return out;
		}
		Node* walker = _ref;
		out << "{";

		while(walker->_next) {
			out << std::to_string(walker->_item) << ", ";
			walker = walker->_next;
		}
		out << std::to_string(walker->_item) << "}";
		return out;
	}
}
#endif //C_CIRCULARLINKEDLIST_H
