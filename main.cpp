/* Data Structures
 * Linked List
 *  - Single
 *  - Double
 *  - Circular Double
 *  - Stack
 *  - Queue
 *  - Hash Table with Linear Probing
 *  - Multi Hash Table
 *  Array List
 *  - Array List (Dynamic array)
 *  Tree
 *  - Binary Tree
 *  - AVL Tree/ WAVL Tree
 *  - Heap
 *  Graph
 *  - Undirected
 *  - Directed
 *  - Directed Acyclic Graph
 *  Algorithms
 *  Sorting
 *  - Linear Sorts
 *  - Comparison Sorts
 *  - Integer Sorts
 *  Searching
 *  - Linear Search
 *  - Binary Search
 *  C++11/14
 *  - Auto
 *  - Lambda
 *  - Smart Pointers
 */


#include <iostream>
#include "DataStructs/Lists/LinkedList.h"
#include "DataStructs/Lists/DoubleLinkedList.h"
#include "DataStructs/Lists/Stack.h"
#include "DataStructs/Lists/Queue.h"
using namespace List;
using namespace std;

void LinkedListOp() {
	LinkedList<int> list;
	std::string input;
	int element, index;
	while(true) {
		try {
			cout << ">> ";
			cin >> input;
			if(input == "quit") {
				exit(0);
			}
			if(input == "insert") {
				cin >> element;
				list.InsertEnd(element);
				list.__print__();
			}
			else if(input == "insertbefore") {
				cin >> element >> index;
				list.InsertBefore(element, index);
				list.__print__();
			}
			else if(input == "insertafter") {
				cin >> element >> index;
				list.InsertAfter(element, index);
				list.__print__();
			}
			else if(input == "remove") {
				cin >> index;
				list.RemoveAt(index);
				list.__print__();
			}
			else if(input == "access") {
				cin >> index;
				cout << list.At(index);
				list.__print__();
			}
			else if(input == "reverse") {
				list = list.Reverse();
				list.__print__();
			}
			else if(input == "sub") {
				int index2;
				cin >> index >> index2;
				list = list.SubList(index, index2);
				list.__print__();
			}
			else if(input == "swap") {
				int index2;
				cin >> index >> index2;
				list.Swap(index, index2);
				list.__print__();
			}
			else if(input == "empty") {
				cout << list.IsEmpty();
			}
			else if(input == "help") {
				cout << "Commands: insert, insertbefore, insertafter, remove, access, reverse, sub, swap, quit";
			}
			else {
				cout << "Bad command";
			}
		}
		catch(Error e) {
			if(e == 0) {
				cout  << "Unexpected Error.";
			}
			else if(e == 2) {
				cout << "Node Not Found.";
			}
			else if(e == 3) {
				cout << "Index Out Of Range.";
			}
		}
		catch(...) {
			cout << "Bad Error";
		}
		cout << endl;
	}
}

int main() {
	try {
		Queue<int> stack;
		stack.Enqueue(1).Enqueue(2).Enqueue(3);
		cout << stack << endl;
		cout << stack.Size() << endl;
		Queue<int> copy(stack);
		cout << copy << endl;
		int a1, a2;
		stack.Dequeue(a1).Dequeue(a2);
		cout << a1 << a2 << endl;
		cout << stack.Size() << endl;
		cout << stack << endl;
		cout << stack.Combine(copy) << endl;

	} catch(...) {
		cout << "Error" << endl;
	}

	return 0;
}