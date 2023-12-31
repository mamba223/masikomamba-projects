//
// ========================================
// HW7: Implement Hash Table with the
// Separate Chaining Technique
// ========================================
//
// In this assignment, we will implement a
// hash table which uses separate chaining
// to deal with collisions. The chains should
// be implemented using singly linked list.
//
// The Node class (used to construct linked list)
// has been defined to you. Do not modify it.
//
// Your task is to develop a HashTable class
// based on the following template.
//
// You should complete six member functions.
//
#include <iostream>
#include <list>
#include "hashtable.h"
using namespace std;
// ------------------------------------
// The Node class is given to you.
// Do not modify it.
// Just use it to construct lists.
// ------------------------------------
class Node {
private:
	int key;
	Node* p_next;
	// there could be other satellite data
	// here we omit them for simplicity
public:
	void Set_key(int x);
	int Get_key();
	void Set_p(Node* p);
	Node* Get_p();
	Node();
};
Node::Node() {
	key = -1;
	p_next = NULL;
}
void Node::Set_key(int x) {
	key = x;
}
int Node::Get_key() {
	return key;
}
void Node::Set_p(Node* p) {
	p_next = p;
}
Node* Node::Get_p() {
	return p_next;
}
//
// -----------------------------------------------
// We will implement a hash table whose elements
// are pointers. Each pointer points to a linked
// list that holds the (collided) students.
//
// The HashTable class is structured as follows.
// Do not modify the structure.
// Your task is to complete the member functions.
// -----------------------------------------------
//
class HashTable {
private:
	// This is the size of the hash table.
	int size;
	// This is the hash function "h".
	// It takes "key" as input and returns
	// a hash code h(key) = key % divisor.
	int hash(int key);
	// This is a pointer to the hash table.
	// Note it is a pointer of pointer.
	Node** table;
public:
	// This function creates a hash table
	// (through dynamic memory allocation)
	// and initializes all cells to NULL.
	//
	// It should create a table of the
	// smallest necessary size N, which
	// depends on the input divisor
	// (of the modulo hash function).
	//
	// This function should also update
	// the private variable "size" to N.
	void CreateTable(int divisor);
	// This function searchs for a student
	// whose SID = key. If a student is found,
	// return address of the student node.
	// Otherwise, return NULL.
	Node* Search(int key);
	// This function adds a student (address
	// stored at "temp") to the hash table.
	void Add(Node* temp);
	// This function removes a student whose
	// SID = key from the table. If the student
	// is not in the table, it does nothing.
	void Remove(int key);
	// This function returns the table size.
	// Specifically, it returns value of the
	// private variable "size".
	int Get_Size();
	// This is the constructor. It is given
	// to you. No need to modify it.
	HashTable();
	// This is the print function. It is given
	// to you and used to examine the correctness
	// your created/updated hash table.
	// Do not modify it.
	void PrintTable();
};
// This is the constructor.
// It is defined for you.
HashTable::HashTable() {
	table = NULL;
	size = 0;
}
// This is the print function.
// It is defined for you.
// Do not modify it.
//
// Basically, this function will
// screen the table line by line,
// and print all SIDS in the linked
// list from head to tail.
//
// This function will be used to
// test if your constructed/updated
// table is correct or not.
void HashTable::PrintTable() {
	Node* temp = NULL;
	for (int i = 0; i < size; i++) {
		temp = table[i];
		while (temp != NULL) {
			cout << temp->Get_key() << '\n';
			temp = temp->Get_p();
		}
	}
}

void HashTable::CreateTable(int divisor) {
	// Dynamically allocate memory for an array of Node* pointers
	table = new Node * [divisor];
	// Store the size of the table
	size = divisor;
	// Initialize each element in the table to NULL
	for (int i = 0; i < divisor; i++) {
		table[i] = NULL;
	}
}

Node* HashTable::Search(int key) {
	// Initialize a temporary pointer to NULL
	Node* temp = NULL;
	// Iterate through each index in the table
	for (int i = 0; i < size; i++) {
		// Set the temporary pointer to the current table index
		temp = table[i];
		// Traverse the linked list at the current index
		while (temp != NULL) {
			// Check if the key of the current node matches the target key
			if (temp->Get_key() == key) {
				// If a match is found, return the pointer to the node
				return temp;
			}
			// Move to the next node in the linked list
			temp = temp->Get_p();
		}
	}
	// If no match is found, return NULL
	return NULL;
}

void HashTable::Add(Node* temp) {
	// Calculate the index where the node should be inserted using a hash function
	int index = hash(temp->Get_key());
	// Set the next pointer of the node to the current head of the linked list
	temp->Set_p(table[index]);
	// Update the head of the linked list to point to the new node
	table[index] = temp;
}

void HashTable::Remove(int key) {
	// Calculate the index where the node to be removed is located using a hash function
	int index = hash(key);

	// Initialize pointers for traversing the linked list
	Node* current = table[index];
	Node* previous = nullptr;

	// Traverse the linked list
	while (current != nullptr) {
		// Check if the key of the current node matches the target key
		if (current->Get_key() == key) {
			// If a match is found, update the pointers to remove the node from the list
			if (previous != nullptr) {
				previous->Set_p(current->Get_p());
			}
			else {
				// If it's the head of the list, update the table's pointer to the next node
				table[index] = current->Get_p();
			}
			// Delete the node
			delete current;
			return;
		}
		// Move to the next node in the linked list
		previous = current;
		current = current->Get_p();
	}
}

int HashTable::Get_Size() {
	// Return the size of the hash table
	return size;
}

int HashTable::hash(int key) {
	// This is a basic hash function that returns the remainder of key divided by the table size.
	return key % size;
}


// --------------
// Main Function
// --------------
int main()
{
	int mode, temp;
	// This key is used as a search key to
	// test the search and remove functions.
	int key;
	// This divisor is used by the hash function.
	// It is also used by the CreateTable() function
	// to automatically determine the table size.
	int divisor;
	Node* Student;
	HashTable x;
	cin >> mode >> key >> divisor;
	x.CreateTable(divisor);
	while (cin >> temp) {
		Student = new Node;
		Student->Set_key(temp);
		x.Add(Student);
	}
	// Mode 0: test if your table size is correct
	if (mode == 0) {
		cout << x.Get_Size();
	}
	// Mode 1: test the "Add" function
	else if (mode == 1) {
		x.PrintTable();
	}
	// Mode 2: test the "Search" function
	else if (mode == 2) {
		Student = x.Search(key);
		if (Student == NULL) {
			cout << -1;
		}
		else {
			cout << Student->Get_key();
		}
	}
	// Mode 3: test the "Remove" function
	else if (mode == 3) {
		x.Remove(key);
		x.PrintTable();
	}
	return 0;
}
