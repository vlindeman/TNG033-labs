#include "set.hpp"
#include <algorithm> 

// Default constructor
Set::Set()
{
	head = new Node(0, nullptr);
}

// Constructor for creating a set from an int
Set::Set(int v)
{
	Node *newNode = new Node(v, nullptr);
	head = new Node(0, newNode);
}

// Constructor creating a set
// a non-sorted array of n intgers
Set::Set(const int a[], int n)
{
	Node *newNode = new Node(0, nullptr);
	head = newNode;

	for (int i = 0; i < n; i++) {
		if (!member(a[i])) { // add if not already part of the set (avoid doublets) 
			Node *nextNode = new Node(a[i], nullptr);
			newNode->next = nextNode;
			newNode = nextNode;
		}
	}
	
	newNode = nullptr;

	// Sort linked list 
	bool unsorted = true;
	while (unsorted) {
		unsorted = false;
		Node *cur = head->next;

		while (cur->next != nullptr) {
			Node *next = cur->next;
			if (cur->value > next->value) {
				const int temp = cur->value;
				const int temp2 = next->value;
				cur->value = temp2;
				next->value = temp;
				unsorted = true;
			}
			cur = cur->next;
		}
	}
	
}


// copy constructor
Set::Set(const Set& source)
{
	head = new Node(0, nullptr);
	Node *p2 = head;
	for (Node *p1 = source.head->next; p1 != nullptr; p1 = p1->next) {
		Node *nextNode = new Node(p1->value, nullptr);
		p2->next = nextNode;
		p2 = nextNode;
	}
}

// Destructor: deallocate all nodes
Set::~Set()
{
	Node * node = head->next; //tmp point to first node

	while (node) { //while still nodes left
		delete head; //delete headnode
		head = node;
		node = node->next; //move to next 
	}

	delete head; //delete last head
}

// Test if set is empty
bool Set::empty() const
{
	if (head->next == nullptr) {
		return true;
	}
	return false;
}

// Return number of elements in the set
int Set::cardinality() const
{
	int counter = 0;
	for (Node *p = head->next; p != nullptr; p = p->next) {
		counter++;
	}
	return counter;
}

// Test if x is an element of the set
bool Set::member(int x) const
{
	for (Node *p = head->next; p != nullptr; p = p->next) {
		if (p->value == x) {
			return true;
		}
	}
	return false;
}

// Assignment operator
Set& Set::operator=(const Set& s)
{
	head = new Node(0, nullptr);
	Node *p2 = head;
	for (Node *p1 = s.head->next;p1 != nullptr; p1 = p1->next) {
		Node *newNode = new Node(p1->value, nullptr);
		p2->next = newNode;
		p2 = newNode;
	}	
	return *this;
}

// returns true if set is a subset of b, otherwise false.
bool Set::operator<=(const Set& b) const
{
	Node *node = head;
	while (node->next) { // loop over every value in b, if not member -> not subset. Elese true 
		if (!b.member(node->next->value)) {
			return false;
		}
		node = node->next;
	}
	return true;
}

// Equal sets 
bool Set::operator==(const Set& b) const
{
	if ((*this <= b) && (b <= *this))
		return true;

	return false;
}

bool Set::operator!=(const Set& b) const
{
	if (!(*this == b))
		return true;

	return false;
}

// Proper subset 
bool Set::operator<(const Set& b) const
{
	if (*this <= b && !(b <= *this)) // return true if this is a subset of b and b is not a subset of this(so that S<S will not be a proper subset )
		return true;

	return false;
}

// Set union
// Repeated values are not allowed
Set Set::operator+(const Set& b) const
{
	Set S;
	Node *S1 = head;
	Node *S2 = b.head;
	Node *S_union = S.head;

	while (S1->next && S2->next)
	{
		if (S1->next->value < S2->next->value)
		{
			insertNode(S, S1->next->value, S_union);
			S1 = S1->next;
		}
		else if (S2->next->value < S1->next->value)
		{
			insertNode(S, S2->next->value, S_union);
			S2 = S2->next;
		}
		else // value s1 == value s2
		{
			insertNode(S, S2->next->value, S_union);
			S1 = S1->next;
			S2 = S2->next;
		}
	}

	while (S1->next) // if there is some part left in S1
	{
		insertNode(S, S1->next->value, S_union);
		S1 = S1->next;
	}

	while (S2->next) // if there is some part left in S2
	{
		insertNode(S, S2->next->value, S_union);
		S2 = S2->next;
	}
	return S;
}

// Set intersection
Set Set::operator*(const Set& b) const
{
	Set resultSet;
	Node *newNode = resultSet.head;

	for (Node *p1 = b.head->next;p1 != nullptr; p1 = p1->next) {
		for (Node *p2 = head->next;p2 != nullptr; p2 = p2->next) {
			if (p2->value == p1->value) {
				Node *nextNode = new Node(p2->value, nullptr);
				newNode->next = nextNode;
				newNode = nextNode;
			}
		}
	}
	return resultSet;
}

// Set difference
Set Set::operator-(const Set& b) const
{
	Set result;
	Node *newNode = result.head;
	bool found = false;

	for (Node *p1 = head->next; p1 != nullptr; p1 = p1->next) {
		for (Node *p2 = b.head->next;p2 != nullptr; p2 = p2->next) {
			if (p2->value == p1->value) {
				found = true;
				break;
			}
		}
		if (!found) {
			Node *nextNode = new Node(p1->value, nullptr);
			newNode->next = nextNode;
			newNode = nextNode;
		}
		found = false;
	}
	return result;
}

// Set union with set {x}
Set Set::operator+(int x) const
{
	Set RE(x);
	return ((*this) + RE);
}

// Set difference with set {x}
Set Set::operator-(int x) const
{
	Set RE(x);
	return ((*this) - RE);
}



std::ostream& operator<<(std::ostream& os, const Set& theSet)
{
	if (theSet.empty())
	{
		os << "Set is empty!";
	}
	else
	{
		Set::Node* temp = theSet.head->next;
		os << "{ ";

		while (temp)
		{
			os << temp->value << " ";
			temp = temp->next;
		}
		os << "}";
	}

	return os;
}


void Set::insertNode(Set &S, int n, Node* &node) const
{
	if (!S.member(n))
	{
		node->next = new Node(n, nullptr);
		node = node->next;
	}
}
