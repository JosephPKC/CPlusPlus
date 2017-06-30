//
// Created by Joe on 6/30/2017.
//

#ifndef C_QUEUE_H
#define C_QUEUE_H
#include "DoubleLinkedList.h"
#include <iostream>
namespace List {
	template <typename T>
	class Queue : public DoubleLinkedList<T> {
		public:
		Queue();
		Queue(const T& item);
		Queue(const Queue<T>& other);
		Queue<T>& operator =(const Queue<T>& other);

		Queue<T>& Enqueue(const T& item);
		T Dequeue();
		Queue<T>& Dequeue(T& out);
		Queue<T>& Combine(const Queue<T>& other);

		T Front() const;
		T Back() const;

		friend std::ostream& operator <<(std::ostream& out, const DoubleLinkedList<T>& other);
	};

	template <typename T>
	Queue<T>::Queue()
			: DoubleLinkedList<T>::DoubleLinkedList() {

	}

	template <typename T>
	Queue<T>::Queue(const T& item)
			: DoubleLinkedList<T>::DoubleLinkedList(item) {

	}

	template <typename T>
	Queue<T>::Queue(const Queue<T>& other)
			: DoubleLinkedList<T>::DoubleLinkedList(other) {

	}

	template <typename T>
	Queue<T>& Queue<T>::operator =(const Queue<T>& other) {
		DoubleLinkedList<T>::operator=(other);
		return *this;
	}

	template <typename T>
	Queue<T>& Queue<T>::Enqueue(const T& item) {
		DoubleLinkedList<T>::InsertEnd(item);
//		std::cout << *this << std::endl;
		return *this;
	}

	template <typename T>
	T Queue<T>::Dequeue() {
		if(DoubleLinkedList<T>::Size() <= 0) {
			throw Error::EMPTY;
		}
		T dequeue = DoubleLinkedList<T>::Access(0);
		DoubleLinkedList<T>::RemoveFront();
		return dequeue;
	}

	template <typename T>
	Queue<T>& Queue<T>::Dequeue(T& out) {
		try {
			out = Dequeue();
			std::cout << *this << std::endl;
			std::cout << DoubleLinkedList<T>::Size() << std::endl;
			return *this;
		}
		catch (Error e) {
			throw e;
		}
	}

	template <typename T>
	Queue<T>& Queue<T>::Combine(const Queue<T>& other) {
		DoubleLinkedList<T>::Append(other);
		return *this;
	}

	template <typename T>
	T Queue<T>::Front() const {
		if(DoubleLinkedList<T>::Size() <= 0) {
			throw Error::EMPTY;
		}
		return DoubleLinkedList<T>::First();
	}

	template <typename T>
	T Queue<T>::Back() const {
		if(DoubleLinkedList<T>::Size() <= 0) {
			throw Error::EMPTY;
		}
		return DoubleLinkedList<T>::Last();
	}

	template <typename T>
	std::ostream& operator <<(std::ostream& out, const Queue<T>& other) {
		out << other.DoubleLinkedList<T>::ToString();
		return out;
	}
}
#endif //C_QUEUE_H
