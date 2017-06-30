//
// Created by Joe on 6/30/2017.
//

#ifndef C_STACK_H
#define C_STACK_H
#include "DoubleLinkedList.h"
#include <iostream>
namespace List {


	template <typename T>
	class Stack : public DoubleLinkedList<T> {

		public:
		Stack();
		Stack(const T& item);
		Stack(const Stack<T>& other);
		Stack<T>& operator =(const Stack<T>& other);


		Stack<T>& Push(const T& element);
		T Pop();
		T Top() const;

		friend std::ostream& operator <<(std::ostream& out, const Stack<T>& other);
	};

	template <typename T>
	Stack<T>::Stack()
			: DoubleLinkedList<T>::DoubleLinkedList() {

	}

	template <typename T>
	Stack<T>::Stack(const T& item)
			: DoubleLinkedList<T>::DoubleLinkedList(item) {

	}

	template <typename T>
	Stack<T>::Stack(const Stack<T>& other)
			: DoubleLinkedList<T>::DoubleLinkedList(other) {

	}

	template <typename T>
	Stack<T>& Stack<T>::operator =(const Stack<T>& other) {
		DoubleLinkedList<T>::operator=(other);
		return *this;
	}

	template <typename T>
	Stack<T>& Stack<T>::Push(const T& element) {
		DoubleLinkedList<T>::InsertFront(element);
		return *this;
	}

	template <typename T>
	T Stack<T>::Pop() {
		if(DoubleLinkedList<T>::Size() <= 0) {
			throw Error::EMPTY;
		}
		T pop = DoubleLinkedList<T>::Access((std::size_t)0);
		DoubleLinkedList<T>::RemoveFront();
		return pop;
	}

	template <typename T>
	T Stack<T>::Top() const {
		if(DoubleLinkedList<T>::Size() > 0)
			return DoubleLinkedList<T>::First();
		else
			throw Error::EMPTY;
	}

	template <typename T>
	std::ostream& operator <<(std::ostream& out, const Stack<T>& other) {
		out << other.DoubleLinkedList<T>::ToString();
		return out;
	}
}
#endif //C_STACK_H
