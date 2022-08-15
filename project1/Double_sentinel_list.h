/*****************************************
 * UW User ID:  h4amjad
 * Name: Hassan Ali Amjad
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Fall 2021
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
	public:
		class Double_node {
			public:
				Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );

				Type value() const;
				Double_node *previous() const;
				Double_node *next() const;

				Type         node_value;
				Double_node *previous_node;
				Double_node *next_node;
		};

		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		Double_sentinel_list( Double_sentinel_list && );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node *begin() const;
		Double_node *end() const;
		Double_node *rbegin() const;
		Double_node *rend() const;

		Double_node *find( Type const & ) const;
		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list );
		Double_sentinel_list &operator=( Double_sentinel_list && );

		void push_front( Type const & );
		void push_back( Type const & );

		void pop_front();
		void pop_back();

		int erase( Type const & );

	private:
		Double_node *list_head;
		Double_node *list_tail;
		int list_size;

		// List any additional private member functions you author here
	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

/*****************************************
 * Double sentinel list constructor: Makes a new 
 * sentinel list by creating two nodes: 
 * the head and tail; assigns the next and 
 * previous node values; takes in no parameters
 *****************************************/

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
	list_head = new Double_sentinel_list::Double_node; 
	list_tail = new Double_sentinel_list::Double_node;  

	list_head -> next_node = list_tail;					
	list_head -> previous_node = nullptr;

	list_tail -> next_node = nullptr;
	list_tail -> previous_node = list_head;
}

/*****************************************
 * Copy constructor not mandatory
 *****************************************/

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
	// Enter your implementation here
}

/*****************************************
 * Move constructor not mandatory
 *****************************************/

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
	// Enter your implementation here
}

/*****************************************
 * Destructor: deletes every element inside linked
 * list, including the sentinel nodes
 *****************************************/

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {

	Double_node *p_temp { nullptr };

	while (list_head != nullptr) {		//loop terminates after tail sentinel
		p_temp = list_head;
		list_head = list_head->next_node;

		delete p_temp;
		p_temp = nullptr;
	}

}

/*****************************************
 * return the size of list
 *****************************************/

template <typename Type>
int Double_sentinel_list<Type>::size() const {
	return list_size;
}

/*****************************************
 * return true if size of list is 0
 *****************************************/

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	
	if(list_size == 0) return true;
	return false;

}

/*
 * return value of first non-sentinel node
 * handles errors by throwing underflow if list
 * is empty
*/

template <typename Type>
Type Double_sentinel_list<Type>::front() const {

	if (list_size == 0) throw underflow();
	return(list_head -> next_node -> node_value);

}

/*****************************************
 * return value of last non-sentinel node
 * handles errors by throwing underflow if list
 * is empty
 *****************************************/

template <typename Type>
Type Double_sentinel_list<Type>::back() const {

	if (list_size == 0) throw underflow();
	return(list_tail -> previous_node -> node_value);

}

/*****************************************
 * returns address of first non sentinel node
 *****************************************/

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
	
	return(list_head -> next_node);

}

/*****************************************
 * returns address of tail sentinel node
 *****************************************/

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
	
	return(list_tail);

}

/*****************************************
 * returns address of last non sentinel node
 *****************************************/

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
	
	return(list_tail -> previous_node);

}

/*****************************************
 * returns address of head sentinel node
 *****************************************/

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
	
	return(list_head);
	
}

/*****************************************
 * finds element in doubly linked list by
 * iterating through it; takes the value to
 * find as a parameter
 *****************************************/

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {

	Double_node *p_temp { nullptr };

	p_temp = list_head -> next_node;		//start at non sentinel node

	while ((p_temp -> next_node) != nullptr) {		//end at last non sentinel node

		if((p_temp -> node_value) == obj) return p_temp;	//return address of equiv node

		p_temp = p_temp -> next_node;	//if not keep iterating
	}
	
	return end();

}

/*****************************************
 * finds frequency of element in a linked list
 * by iterating through it and incrememnting count
 * where value to find is passed into fxn
 *****************************************/

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
	
	int count = 0;

	Double_node *p_temp { nullptr };

	p_temp = list_head -> next_node;

	while ((p_temp -> next_node) != nullptr) {

		if((p_temp -> node_value) == obj) count++;

		p_temp = p_temp -> next_node;
	}
	
	return count;
	
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	// This is done for you
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

// The assignment operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

// The move operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

/*****************************************
 * Push node to front of linked list, with the
 * value passed in as the parameter obj
 *****************************************/

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
	
	Double_node *new_node = new Double_sentinel_list::Double_node(obj, list_head, (list_head -> next_node)); //initialize new node with val, prev, and next pointers

	list_head -> next_node -> previous_node = new_node; //second node's previous node is the new node
	list_head -> next_node = new_node;					//head's next node is new node

	list_size++;

}

/*****************************************
 * Push node to back of linked list, with the
 * value passed in as the parameter obj
 *****************************************/

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {

	Double_node *new_node = new Double_sentinel_list::Double_node(obj, (list_tail -> previous_node), list_tail);	//initialize new node with val, prev, and next pointers

	list_tail -> previous_node -> next_node = new_node;	//second last nodes next node is new node
	list_tail -> previous_node = new_node;				//tails previous node is the new node

	list_size++;
	
}

/*****************************************
 * Pop the front element of linked list, and
 * if list is empty, throw an underflow error
 *****************************************/

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {

	if (list_size == 0) throw underflow();

	Double_node *pop_node {nullptr};
	pop_node = list_head -> next_node;	//store fist node using temporary node

	pop_node -> next_node -> previous_node = list_head;		//set previous node of second node to list head
	list_head -> next_node = pop_node -> next_node;			//set next node of list head to second node

	delete pop_node;		//delete node 
	pop_node = nullptr;

	list_size--;

}

/*****************************************
 * Pop the last element of linked list, and
 * if list is empty, throw an underflow error
 *****************************************/

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {

	if (list_size == 0) throw underflow();

	Double_node *pop_node {nullptr};
	pop_node = list_tail -> previous_node;	//store last node using temporary node

	pop_node -> previous_node -> next_node = list_tail;			//set next node of second last node to list tail
	list_tail -> previous_node = pop_node -> previous_node;		//set previous node of list tail to second last node

	delete pop_node;		//delete node 
	pop_node = nullptr;

	list_size--;
	
}

/*****************************************
 * Erase all instances of nodes that have the
 * same value as the obj passed in as a parameter
 * and return how many instances were deleted
 *****************************************/

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {

	int count = 0;

	Double_node *p_temp { nullptr };

	p_temp = list_head -> next_node;		//initialize temp pointer to first node

	while ((p_temp -> next_node) != nullptr) {			//iterate through list until last non-sentinel node reached

		if((p_temp -> node_value) == obj){				//if node with same value as obj found:

			count++;

			Double_node *p_real1 {nullptr};
			Double_node *p_real2 {nullptr};
			p_real1 = p_temp -> previous_node;			//store prev and next nodes of pointer to be deleted
			p_real2 = p_temp -> next_node;

			p_temp -> previous_node -> next_node = p_real2;			//previous' next = temp's next
			p_temp -> next_node -> previous_node = p_real1;			//next's previous = temp's previous

			delete p_temp;					//delete node
			p_temp = nullptr;

			list_size--;

			p_temp = p_real2;			//continue iterating

		} else {

			p_temp = p_temp -> next_node;		//normal iteration if value doesn't match
		
		}

	}

	return count;

}

/*****************************************
 * constructor to initialize a new node, with
 * following membor variables: initialized to type and
 * nullptr; otherwise to the parameters passed in, the
 * value, previous node and next node
 *****************************************/

template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const &nv,
	typename Double_sentinel_list<Type>::Double_node *pn,
	typename Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here
node_value( Type() ), // This assigns 'node_value' the default value of Type
previous_node( nullptr ),
next_node( nullptr )
{
	node_value = nv;
	previous_node = pn;
	next_node = nn;
}

/*****************************************
 * return value of node
 *****************************************/

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	return node_value;
}

/*****************************************
 * return previous node address
 *****************************************/

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	return previous_node;
}

/*****************************************
 * return next node address
 *****************************************/

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	return next_node;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.rend(); ptr != nullptr; ptr = ptr->next() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.end(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0";

	return out;
}

#endif
