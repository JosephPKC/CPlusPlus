//
// Created by Joe on 6/28/2017.
//

#ifndef C_DOUBLELINKEDLIST_H
#define C_DOUBLELINKEDLIST_H

namespace List {
	template <typename T>
	class DoubleLinkedList {
		private:
		struct Node {
			T _item;
			Node* _next;
			Node* _prev;

			// Constructor. Sets next and prev to null.
			Node(const T& item)
					: _item(item), _next(nullptr), _prev(nullptr) {};

			// Prints out the next-wise chain and the previous-wise chains
			void Relations() {
				std::cout << "Next-wise: ";
				Node* walker = this;
				while(walker->_next) {
					std::cout << walker->_item << ", ";
					walker = walker->_next;
				}
				std::cout << walker->_item << std::endl;
				std::cout << "Previous-wise: ";
				while(walker->_prev) {
					std::cout << walker->_item << ", ";
					walker = walker->_prev;
				}
				std::cout << walker->_item << std::endl;
			}

			// Prints out the items in order
			friend std::ostream& operator <<(std::ostream& out, const Node& node) {
				out << node._item;
				if(node._next) {
					out << ", " << *node._next;
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

		//Makes a new head
		void MakeNew(const T& item);
		// Calculates the Size of the chain
		std::size_t Count() const;
		// Returns the node associated with the index
		Node* FromIndex(std::size_t index) const;
		// Constructs a List based on the node
		DoubleLinkedList(Node* node);
		public:
		//Constructs an empty List
		DoubleLinkedList();
		//Constructs a single item List
		DoubleLinkedList(const T& item);
		//Constructs a List from the array
		DoubleLinkedList(T array[], std::size_t size);
		//Constructs a List from another List (copies)
		DoubleLinkedList(const DoubleLinkedList<T>& other);
		//Constucts a List from another List
		DoubleLinkedList<T>& operator =(const DoubleLinkedList<T>& other);
		//Destructor
		~DoubleLinkedList();
		//Inserts an item before the index
		DoubleLinkedList<T>& InsertBefore(const T& item, std::size_t index);
		//Inserts an item after the index
		DoubleLinkedList<T>& InsertAfter(const T& item, std::size_t index);
		//Inserts an item as the first
		DoubleLinkedList<T>& InsertFront(const T& item);
		//Inserts an item as the last
		DoubleLinkedList<T>& InsertEnd(const T& item);
		//Appends a list to the end
		DoubleLinkedList<T>& Append(const DoubleLinkedList<T>& other);
		//Modifies the node at the index
		DoubleLinkedList<T>& Modify(const T& item, std::size_t index);
		//Removes the node at the index
		DoubleLinkedList<T>& Remove(std::size_t index);
		//Removes the first node
		DoubleLinkedList<T>& RemoveFront();
		//Removes the last node
		DoubleLinkedList<T>& RemoveEnd();
		//Returns a copy of the item at the index
		T Access(std::size_t index) const;
		//Returns the reference of the item at the index (mutable)
		T& Access(std::size_t index);
		//Returns a copy of the first item
		T First() const;
		//Returns the reference of the first item
		T& First();
		//Returns a copy of the last item
		T Last() const;
		//Returns the refence of the last item
		T& Last();
		//Returns a copy of the item at the index
		T operator [](std::size_t index) const;
		//Returns the reference of the item at the index
		T& operator [](std::size_t index);
		//Returns the size of the list
		std::size_t Size() const;
		//Returns whether the list is empty or not
		bool IsEmpty() const;
		//Returns a string representation of the list
		std::string ToString() const;
		//Returns an array representation of the list
		T* ToArray() const;
		//Returns the reverse of the list
		DoubleLinkedList<T> Reverse() const;
		//Returns a sub list
		DoubleLinkedList<T> SubList(std::size_t from, std::size_t to) const;
		//Swaps two items in the list
		void Swap(std::size_t first, std::size_t second);
		//Prints the items in the list in order
		friend std::ostream& operator <<(std::ostream& out, const DoubleLinkedList<T>& other);
	};

	template <typename T>
	void DoubleLinkedList<T>::MakeNew(const T& item) {
		_head = new Node(item);
		_size = 1;
		_tail = _head;
	}
	template <typename T>
	std::size_t DoubleLinkedList<T>::Count() const {
		Node* hWalker = _head;
		Node* tWalker = _tail;
		std::size_t count = 0;
		while(hWalker != tWalker && hWalker->_prev != tWalker) {
			count += 2;
			hWalker = hWalker->_next;
			tWalker = tWalker->_prev;
		}
		if(hWalker == tWalker) {
			++count;
		}
		return count;
	}
	template <typename T>
	typename DoubleLinkedList<T>::Node* DoubleLinkedList<T>::FromIndex(std::size_t index) const {
		if(index >= _size)
			return nullptr;
		std::size_t count = 0;
		//First determine whether the head or the tail is closer
		if(index > _size / 2) {
			//Use the tail
			index = _size - index - 1;
			Node* walker = _tail;
			while(walker) {
				if(index == count) {
					return walker;
				}
				walker = walker->_prev;
				++count;
			}
		}
		else {
			//Use the head
			Node* walker = _head;
			while(walker) {
				if(index == count) {
					return walker;
				}
				walker = walker->_next;
				++count;
			}
		}
		return nullptr;
	}
	template <typename T>
	DoubleLinkedList<T>::DoubleLinkedList(Node* node) {
		_head = node;
		_size = Count();
		_tail = FromIndex(_size - 1);
	}
	template <typename T>
	DoubleLinkedList<T>::DoubleLinkedList() {
		_head = nullptr;
		_tail = nullptr;
		_size = 0;
	}
	template <typename T>
	DoubleLinkedList<T>::DoubleLinkedList(const T& item) {
		_head = new Node(item);
		_tail = _head;
		_size = 1;
	}
	template <typename T>
	DoubleLinkedList<T>::DoubleLinkedList(T array[], std::size_t size) {
		if(size == 0) {
			_head = nullptr;
			_tail = nullptr;
			_size = 0;
		}
		else {
			Node* head = new Node(array[0]);
			_head = head;
			_size = size;
			Node* walker = _head;
			for(int i = 1; i < size; ++i) {
				Node* temp = new Node(array[i]);
				temp->_prev = walker;
				walker->_next = temp;
				walker = walker->_next;
			}
			_tail = walker;
		}
	}
	template <typename T>
	DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T>& other) {
		if(!other._head) {
			_head = nullptr;
			_tail = nullptr;
			_size = 0;
		}
		else {
			_size = other._size;
			_head = new Node(other._head->_item);
			Node* walker = _head;
			Node* walkerOther = other._head->_next;
			while(walkerOther) {
				Node* temp = new Node(walkerOther->_item);
				temp->_prev = walker;
				walker->_next = temp;
				walker = walker->_next;
				walkerOther = walkerOther->_next;
			}
			_tail = walker;
		}
	}
	template <typename T>
	DoubleLinkedList<T>& DoubleLinkedList<T>::operator =(const DoubleLinkedList<T>& other) {
		if(!other._head) {
			_head = nullptr;
			_tail = nullptr;
			_size = 0;
		}
		else {
			_size = other._size;
			_head = new Node(other._head->_item);
			Node* walker = _head;
			Node* walkerOther = other._head->_next;
			while(walkerOther) {
				Node* temp = new Node(walkerOther->_item);
				temp->_prev = walker;
				walker->_next = temp;
				walker = walker->_next;
				walkerOther = walkerOther->_next;
			}
			_tail = walker;
		}
	}
	template <typename T>
	DoubleLinkedList<T>::~DoubleLinkedList() {
		while(_head) {
			Node* temp = _head;
			_head = _head->_next;
			delete temp;
		}
	}
	template <typename T>
	DoubleLinkedList<T>& DoubleLinkedList<T>::InsertBefore(const T& item, std::size_t index) {
		if(!_head) {
			MakeNew(item);
			return *this;
		}
		else {
			Node* newNode = new Node(item);
			if(index == 0) {
				newNode->_next = _head;
				_head->_prev = newNode;
				_head = newNode;
			}
			else {
				Node* after = FromIndex(index);
				Node* before = FromIndex(index - 1);
				before->_next = newNode;
				newNode->_prev = before;
				newNode->_next = after;
				after->_prev = newNode;
			}
			++_size;
			return *this;
		}
	}
	template <typename T>
	DoubleLinkedList<T>& DoubleLinkedList<T>::InsertAfter(const T& item, std::size_t index) {
		if(index >= _size) {
			return *this;
		}
		if(!_head) {
			MakeNew(item);
			return *this;
		}
		else {
			Node* newNode = new Node(item);
			if(index == _size - 1) {
				newNode->_prev = _tail;
				_tail->_next = newNode;
				_tail = newNode;
			}
			else {
				Node* after = FromIndex(index + 1);
				Node* before = FromIndex(index);
				before->_next = newNode;
				newNode->_prev = before;
				newNode->_next = after;
				after->_prev = newNode;
			}
			++_size;
			return *this;
		}
	}
	template <typename T>
	DoubleLinkedList<T>& DoubleLinkedList<T>::InsertFront(const T& item) {
		return InsertBefore(item, 0);
	}
	template <typename T>
	DoubleLinkedList<T>& DoubleLinkedList<T>::InsertEnd(const T& item) {
		if(_size == 0)
			_size = 1;
		InsertAfter(item, _size - 1);
		return *this;
	}
	template <typename T>
	DoubleLinkedList<T>& DoubleLinkedList<T>::Append(const DoubleLinkedList<T>& other) {
		if(other.IsEmpty()) {
			return *this;
		}
		_tail->_next = other._head;
		other._head->_prev = _tail;
		_tail = other._tail;
		_size += other._size;
		return *this;
	}
	template <typename T>
	DoubleLinkedList<T>& DoubleLinkedList<T>::Modify(const T& item, std::size_t index) {
		Node* thisNode = FromIndex(index);
		if(thisNode) {
			thisNode->_item = item;
		}
		return *this;
	}
	template <typename T>
	DoubleLinkedList<T>& DoubleLinkedList<T>::Remove(std::size_t index) {
		if(!_head) {
			return *this;
		}
		if(index >= _size) {
			return *this;
		}
		Node* deleteNode;
		if(index == 0) {
			deleteNode = _head;
			if(_size != 1) {
				_head = _head->_next;
				_head->_prev = nullptr;
			}
			else {
				_head = _tail = nullptr;
			}
		}
		else if(index == _size - 1){
			deleteNode = _tail;
			_tail = _tail->_prev;
			_tail->_next = nullptr;
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
	DoubleLinkedList<T>& DoubleLinkedList<T>::RemoveFront() {
		return Remove(0);
	}
	template <typename T>
	DoubleLinkedList<T>& DoubleLinkedList<T>::RemoveEnd() {
		return Remove(_size - 1);
	}
	template <typename T>
	T DoubleLinkedList<T>::Access(std::size_t index) const {
		return FromIndex(index)->_item;
	}
	template <typename T>
	T& DoubleLinkedList<T>::Access(std::size_t index) {
		return FromIndex(index)->_item;
	}
	template <typename T>
	T DoubleLinkedList<T>::First() const {
		return _head->_item;
	}
	template <typename T>
	T& DoubleLinkedList<T>::First() {
		return _head->_item;
	}
	template <typename T>
	T DoubleLinkedList<T>::Last() const {
		return _tail->_item;
	}
	template <typename T>
	T& DoubleLinkedList<T>::Last() {
		return _tail->_item;
	}
	template <typename T>
	T DoubleLinkedList<T>::operator [](std::size_t index) const {
		return Access(index);
	}
	template <typename T>
	T& DoubleLinkedList<T>::operator [](std::size_t index) {
		return Access(index);
	}
	template <typename T>
	std::size_t DoubleLinkedList<T>::Size() const {
		return _size;
	}
	template <typename T>
	bool DoubleLinkedList<T>::IsEmpty() const {
		return !_head;
	}
	template <typename T>
	std::string DoubleLinkedList<T>::ToString() const {
		Node* walker = _head;
		std::string repr = "{";
		if(!_head) {
			repr += "}";
			return repr;
		}
		while(walker->_next) {
			repr += std::to_string(walker->_item) + ", ";
			walker = walker->_next;
		}
		repr += std::to_string(walker->_item) + "}";
		return repr;
	}
	template <typename T>
	T* DoubleLinkedList<T>::ToArray() const {
		if(!_head) {
			return nullptr;
		}
		Node* walker = _head;
		T* array = new T[_size];
		for(std::size_t i = 0; i < _size; ++i) {
			array[i] = walker->_item;
			walker = walker->_next;
		}
		return array;
	}
	template <typename T>
	DoubleLinkedList<T> DoubleLinkedList<T>::Reverse() const {
		if(!_head) {
			return DoubleLinkedList<T>();
		}
		DoubleLinkedList<T> reversed(*this);
		Node* walker = reversed._head;
		Node* rWalker = reversed._tail;
		while(walker != rWalker && walker->_prev != rWalker) {
			T temp = walker->_item;
			walker->_item = rWalker->_item;
			rWalker = temp;
			walker = walker->_next;
			rWalker = rWalker->_prev;
		}
		return reversed;
	}
	template <typename T>
	DoubleLinkedList<T> DoubleLinkedList<T>::SubList(std::size_t from, std::size_t to) const {
		if(from > to) {
			return DoubleLinkedList<T>();
		}
		else if(from == to) {
			return DoubleLinkedList<T>(FromIndex(from)->_item);
		}
		else {
			Node* fromNode = FromIndex(from);
			Node* toNode = FromIndex(to);
			Node* subHead = new Node(fromNode->_item);
			Node* walker = subHead;
			fromNode = fromNode->_next;
			while(fromNode->_prev != toNode) {
				walker->_next = new Node(fromNode->_item);
				walker = walker->_next;
				fromNode = fromNode->_next;
			}
			return LinkedList<T>(subHead);
		}
	}
	template <typename T>
	void DoubleLinkedList<T>::Swap(std::size_t first, std::size_t second) {
		Node* firstNode = FromIndex(first);
		Node* secondNode = FromIndex(second);
		T temp = firstNode->_item;
		firstNode->_item = secondNode->_item;
		secondNode->_item = temp;
	}
	template <typename T>
	std::ostream& operator <<(std::ostream& out, const DoubleLinkedList<T>& other) {
		out << other.ToString();
		return out;
	}
	/**/
 }



#endif //C_DOUBLELINKEDLIST_H
