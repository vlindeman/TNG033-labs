#ifndef SET_H
#define SET_H

#include <iostream>

class Set 
{
public:
    // Default constructor
    Set();

    // Constructor for creating a set from an int
    explicit Set(int v);

    // Constructor creating a set
    // from n integers in a non-sorted array a
    Set(const int a[], int n);

    // copy constructor
    Set(const Set& b);  // must receive a reference to avoid infinite recursion

    // assignment operator
    Set& operator=(const Set& b);

    // destructor
    ~Set();

    bool empty() const;        // Test if set is empty
    int cardinality() const;   // Return number of elements in the set
    bool member(int x) const;  // Test if x is an element of the set

    // Overloaded operators
    // A new set is returned
    Set operator+(const Set& b) const;  // Set union
    Set operator*(const Set& b) const;  // Set intersection
    Set operator-(const Set& b) const;  // Set difference
    Set operator+(int x) const;         // set union with set {x}
    Set operator-(int x) const;         // set difference with set {x}

    // Overloaded comparison operators
    bool operator<=(const Set& b) const;
    bool operator==(const Set& b) const;
    bool operator!=(const Set& b) const;
    bool operator<(const Set& b) const;

private:
    // This class is private to class Set
    // but all class Node members are public to class Set
    class Node 
	{
    public:
        // Constructor
        Node(int nodeVal, Node* nextPtr) : value(nodeVal), next(nextPtr) {}

        int value;
        Node* next;

        friend std::ostream& operator<<(std::ostream& os, const Set& b);
    };

    Node* head;  // points to the first node
    // Note: first node is a dummy node of the list

    friend std::ostream& operator<<(std::ostream& os, const Set& b);

    /* Auxiliarly functions */
    // Add any, if needed
	void insertNode(Set &S, int n, Node* &node) const;
};

#endif
