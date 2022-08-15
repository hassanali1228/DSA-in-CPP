/*****************************************
 * UW User ID:  h4amjad
 * Name: Hassan Ali Amjad
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 *****************************************/

#ifndef DYNAMIC_DEQUE_H
#define DYNAMIC_DEQUE_H

#include "Exception.h"
#include <iostream>				//added for last function in file

template <typename Type>
class Resizable_deque {
	public:
		Resizable_deque( int = 16 );
		Resizable_deque( Resizable_deque const & );
		Resizable_deque( Resizable_deque && );
		~Resizable_deque();

		Type front() const;
		Type back() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void swap( Resizable_deque & );
		Resizable_deque &operator=( Resizable_deque const& );
		Resizable_deque &operator=( Resizable_deque && );
		void push_front( Type const & );
		void push_back( Type const & );
		void pop_front();
		void pop_back();
		void clear();

	private:
		// Your member variables

		// Any private member functions
		//   - helper functions for resizing your array?

		int ifront;
		int iback;
		int deque_size;
		int initial_array_capacity;		//can't go below this
		int array_capacity;
		Type *array;

		void resize_array(bool doubled);

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Resizable_deque<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                   Constructors and Destructors                      //
/////////////////////////////////////////////////////////////////////////

// Constructor
/*****************************************
 * Initialize new deque where n is the capacity you want
 * as long as n is larger than 16, and also initializes
 * back and front pointers in circular array
 *****************************************/
template <typename Type>
Resizable_deque<Type>::Resizable_deque( int n ):
deque_size (0),
initial_array_capacity (16),
ifront (0),
iback (-1)
{
	initial_array_capacity = std::max(16,n);
	array_capacity = initial_array_capacity;

	array = new Type[array_capacity];
}

// Copy Constructor
/*****************************************
 * Takes in existing deque, and creates new deque using circular array
 * by looping through it and pasting it into a new array object
 *****************************************/
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque const &deque ):
deque_size (0),
initial_array_capacity (deque.initial_array_capacity),
array_capacity (deque.array_capacity),
ifront (0),
iback (-1)
{
	array = new Type[array_capacity];
	
	for(int i = 0; i <= deque.array_capacity; ++i){

		array[i] = deque.array[i];
		++deque_size;

	}
}

// Move Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque &&deque )
// Your initalization list
{
	// Enter your implementation here
}

// Destructor
/*****************************************
 * Deletes the dynamic array and sets it to nullptr
 *****************************************/
template <typename Type>
Resizable_deque<Type>::~Resizable_deque() {
	
	delete [] array;
	array = nullptr;

}

/////////////////////////////////////////////////////////////////////////
//                     Public Member Functions                         //
/////////////////////////////////////////////////////////////////////////

/*****************************************
 * return size of deque
 *****************************************/
template <typename Type>
int Resizable_deque<Type>::size() const {
	
	return deque_size;

}

/*****************************************
 * return current capacity of array
 *****************************************/
template <typename Type>
int Resizable_deque<Type>::capacity() const {
	
	return array_capacity;

}

/*****************************************
 * return if the list is empty (deque size is 0)
 *****************************************/
template <typename Type>
bool Resizable_deque<Type>::empty() const {
	
	return (deque_size == 0);

}

/*****************************************
 * return front of the array, if list is empty
 * throw underflow error
 *****************************************/
template <typename  Type>
Type Resizable_deque<Type>::front() const {
	if(deque_size == 0) throw underflow();
	return array[ifront];
}

/*****************************************
 * return back of the array, if list is empty
 * throw underflow error
 *****************************************/
template <typename  Type>
Type Resizable_deque<Type>::back() const {
	if(deque_size == 0) throw underflow();
	return array[iback];
}

/*****************************************
 * swap all memeber variables with the memeber variables
 * of the deque passed as a parameter
 *****************************************/
template <typename Type>
void Resizable_deque<Type>::swap( Resizable_deque<Type> &deque ) {
	// Swap the member variables
	//     std::swap( variable, deque.variable );

	std::swap(ifront, deque.ifront);
	std::swap(iback, deque.iback);
	std::swap(deque_size, deque.deque_size);
	std::swap(initial_array_capacity, deque.initial_array_capacity);
	std::swap(array, deque.array);
	
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> const &rhs ) {
	// This is done for you...
	Resizable_deque<Type> copy( rhs );
	swap( copy );

	return *this;
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> &&rhs ) {
	// This is done for you...
	swap( rhs );

	return *this;
}

/*****************************************
 * push object passed as a parameter to the front of the
 * deque, and if deque is full, call helper function to resize
 * after doubling capacity. Also if list is empty initially, set iback
 * and ifront to end of array.
 *****************************************/
template <typename Type>
void Resizable_deque<Type>::push_front( Type const &obj ) {
	
	if(deque_size == array_capacity){

		array_capacity *= 2;
		resize_array(true);			//need to double array

	}

	if (ifront == 0 && iback == -1){
		ifront = array_capacity-1;
		iback = array_capacity-1;
	}
	
	else if (ifront == 0 ) ifront = array_capacity-1;
	else --ifront;

	array[ifront] = obj;
	++deque_size;

}

/*****************************************
 * push object passed as a parameter to the back of the deque,
 *  and if deque is full, call helper function to resize
 * after doubling capacity. Also if list is empty initially, set iback
 * and ifront to end of array.
 *****************************************/
template <typename Type>
void Resizable_deque<Type>::push_back( Type const &obj ) {

	if(deque_size == array_capacity){

		array_capacity *= 2;
		resize_array(true);			//need to double array

	}

	if (ifront == 0 && iback == -1){
		iback = 0;
	}

	else if (iback == array_capacity-1) iback = 0;
	else ++iback;

	array[iback] = obj;
	++deque_size;

}

/*****************************************
 * pop object from front of the deque, and if list is empty
 * throw an underflow error. If deque is quarter the size of capacity 
 * (and > initial), call helper function to resize after halfing
 * capacity.
 *****************************************/
template <typename Type>
void Resizable_deque<Type>::pop_front() {

	// std::cout << array[ifront] << std::endl;

	if (deque_size == 0) throw underflow();

	array[ifront] = 1431655765;

	if(ifront == iback){	//all elements deleted; reset
		iback = -1;
		ifront = 0;
	}
	
	if (ifront == array_capacity-1) ifront = 0;
	else ++ifront;

	--deque_size;

	if ( (deque_size <= array_capacity/4) && (initial_array_capacity <= array_capacity/2) ){

		array_capacity /= 2;
		resize_array(false);			//need to half array

	}

}

/*****************************************
 * pop object from back of the deque, and if list is empty
 * throw an underflow error. If deque is quarter the size of capacity 
 * (and > initial), call helper function to resize after halfing
 * capacity.
 *****************************************/
template <typename Type>
void Resizable_deque<Type>::pop_back() {

	if (deque_size == 0) throw underflow();
	
	array[iback] = 1431655765;

	if(ifront == iback){	//all elements deleted; reset
		iback = -1;
		ifront = 0;
	}

	else if (iback == 0) iback = array_capacity-1;
	else --iback;

	--deque_size;

	if ( (deque_size <= array_capacity/4) && (initial_array_capacity <= array_capacity/2) ){
		
		array_capacity /= 2;
		resize_array(false);			//need to half array

	}

}

/*****************************************
 * clear resets all member variables to their
 * default state
 *****************************************/
template <typename Type>
void Resizable_deque<Type>::clear() {
	
	array_capacity = initial_array_capacity;
	ifront = 0;
	iback = -1;
	deque_size = 0;

	// delete [] array;
	array = new Type [array_capacity];
	
}
/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

/*****************************************
 * helper function to resize array that takes in bool parameter to 
 * tell if array is being doubled or not, by creating array
 * of the new capacity, and populating new array with all
 * the elements from front to back of the previous array.
 * Reassign array ptr and ifront & iback.
 *****************************************/
template <typename Type>
void Resizable_deque<Type>::resize_array(bool doubled){

	Type *temparray;

	temparray = new Type[array_capacity];

	int i = ifront;
	int j = 0;

	while(i != iback){

		temparray[j] = array[i];

		if( (i == deque_size-1 && doubled == 1) || (i == (array_capacity*2)-1 && doubled == 0) ){

			i = 0;

		} else {

			i++;

		}
		
		j++;

	}

	temparray[j] = array[i];

	delete [] array;
	array = temparray;

	ifront = 0;
	iback = deque_size-1;

}


/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Resizable_deque<T> const &list ) {

	std::cout << "size: " << list.deque_size << std::endl;	

	for (int i = 0; i < list.array_capacity; ++i){

		if (list.array[i] != 1431655765) std::cout << list.array[i] << " ";
		else std::cout << "None" << " ";

	}
	

	return out;
}

#endif
