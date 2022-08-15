/*****************************************
 * UW User ID:  h4amjad
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By  submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef RPOVDGBQN9TIEO3P
#define RPOVDGBQN9TIEO3P

#include "Exception.h"
#include "ece250.h"
#include <cassert>

template <typename Type>
class Search_tree {
	public:
		class Iterator;

	private:
		class Node {
			public:
				Type node_value;
				int tree_height;

				// The left and right sub-trees
				Node *left_tree;
				Node *right_tree;

				// Hint as to how you can create your iterator
				// Point to the previous and next nodes in linear order
				Node *previous_node;
				Node *next_node;

				// Member functions
				Node( Type const & = Type(), Node * = nullptr, Node * = nullptr ); //data, next node, previous node
					//modified constructor to take in next and previous pointers

				void update_height();

				int height() const;
				bool is_leaf() const;
				Node *front();
				Node *back();
				Node *find( Type const &obj );

				void clear();
				bool insert( Type const &obj, Node *&to_this );
				bool erase( Type const &obj, Node *&to_this );

				void balance( Node *&curr_node );		//called after insertion or deletion
				void rotate_left( Node *&curr_node );	//helpers for rotating trees
				void rotate_right(Node *&curr_node );
				int check_balance();					//returns a factor by which balance is off

		};

		Node *root_node;
		int tree_size;

		// Hint as to how to start your linked list of the nodes in order 
		Node *front_sentinel;
		Node *back_sentinel;

	public:
		class Iterator {
			private:
				Search_tree *containing_tree;
				Node *current_node;
				bool is_end;

				// The constructor is private so that only the search tree can create an iterator
				Iterator( Search_tree *tree, Node *starting_node );

			public:
				// DO NOT CHANGE THE SIGNATURES FOR ANY OF THESE
				Type operator*() const;
				Iterator &operator++();
				Iterator &operator--();
				bool operator==( Iterator const &rhs ) const;
				bool operator!=( Iterator const &rhs ) const;

			// Make the search tree a friend so that it can call the constructor
			friend class Search_tree;
		};

		// DO NOT CHANGE THE SIGNATURES FOR ANY OF THESE
		Search_tree();
		~Search_tree();

		bool empty() const;
		int size() const;
		int height() const;

		Type front() const;
		Type back() const;

		Iterator begin();
		Iterator end();
		Iterator rbegin();
		Iterator rend();
		Iterator find( Type const & );

		void clear();
		bool insert( Type const & );
		bool erase( Type const & );

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Search_tree<T> const & );
};

//////////////////////////////////////////////////////////////////////
//                Search Tree Public Member Functions               //
//////////////////////////////////////////////////////////////////////

// The initialization of the front and back sentinels is a hint
template <typename Type>
Search_tree<Type>::Search_tree():
root_node( nullptr ),
tree_size( 0 ),
front_sentinel( new Search_tree::Node( Type() ) ),
back_sentinel( new Search_tree::Node( Type() ) ) {
	front_sentinel->next_node = back_sentinel;
	back_sentinel->previous_node = front_sentinel;
}

template <typename Type>
Search_tree<Type>::~Search_tree() {
	clear();  // might as well use it...
	delete front_sentinel;
	delete back_sentinel;
}

template <typename Type>
bool Search_tree<Type>::empty() const {
	return ( root_node == nullptr );
}

template <typename Type>
int Search_tree<Type>::size() const {
	return tree_size;
}

template <typename Type>
int Search_tree<Type>::height() const {
	return root_node->height();
}

template <typename Type>
Type Search_tree<Type>::front() const {
	if ( empty() ) {
		throw underflow();
	}

	return root_node->front()->node_value;
}

template <typename Type>
Type Search_tree<Type>::back() const {
	if ( empty() ) {
		throw underflow();
	}

	return root_node->back()->node_value;
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::begin() {
	return empty() ? Iterator( this, back_sentinel ) : Iterator( this, root_node->front() );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::end() {
	return Iterator( this, back_sentinel );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::rbegin() {
	return empty() ? Iterator( this, front_sentinel ) : Iterator( this, root_node->back() );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::rend() {
	return Iterator( this, front_sentinel );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::find( Type const &obj ) {
	if ( empty() ) {
		return Iterator( this, back_sentinel );
	}

	typename Search_tree<Type>::Node *search_result = root_node->find( obj );

	if ( search_result == nullptr ) {
		return Iterator( this, back_sentinel );
	} else {
		return Iterator( this, search_result );
	}
}

template <typename Type>
void Search_tree<Type>::clear() {
	if ( !empty() ) {
		root_node->clear();
		root_node = nullptr;
		tree_size = 0;
	}

	// Reinitialize the sentinels
	front_sentinel->next_node = back_sentinel;
	back_sentinel->previous_node = front_sentinel;
}

template <typename Type>
bool Search_tree<Type>::insert( Type const &obj ) {
	if ( empty() ) {
		root_node = new Search_tree::Node( obj,  back_sentinel, front_sentinel );		//initialize next and previous pointers to back and front sentinels
	
		front_sentinel->next_node = root_node;			//set front and back sentinels' next and prev nodes accordingly
		back_sentinel->previous_node = root_node;

		tree_size = 1;

		return true;
	} else if ( root_node->insert( obj, root_node ) ) {
		++tree_size;
		return true;
	} else {
		return false;
	}
}

template <typename Type>
bool Search_tree<Type>::erase( Type const &obj ) {
	if ( !empty() && root_node->erase( obj, root_node ) ) {
		--tree_size;
		return true;
	} else {
		return false;
	}
}

//////////////////////////////////////////////////////////////////////
//                   Node Public Member Functions                   //
//////////////////////////////////////////////////////////////////////

template <typename Type>
Search_tree<Type>::Node::Node( Type const &obj,
	typename Search_tree<Type>::Node *nn,			//modified node class to take front and back pointers
	typename Search_tree<Type>::Node *pn ):
node_value( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
next_node( nullptr ),
previous_node( nullptr ),
tree_height( 0 ) {

	next_node = nn;			//if parameters passed, use these
	previous_node = pn;

}

template <typename Type>
void Search_tree<Type>::Node::update_height() {
	tree_height = std::max( left_tree->height(), right_tree->height() ) + 1;
}

template <typename Type>
int Search_tree<Type>::Node::height() const {
	return ( this == nullptr ) ? -1 : tree_height;
}

// Return true if the current node is a leaf node, false otherwise
template <typename Type>
bool Search_tree<Type>::Node::is_leaf() const {
	return ( (left_tree == nullptr) && (right_tree == nullptr) );
}

// Return a pointer to the front node
template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::front() {
	return ( left_tree == nullptr ) ? this : left_tree->front();
}

// Return a pointer to the back node
template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::back() {
	return ( right_tree == nullptr ) ? this : right_tree->back();
}

template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::find( Type const &obj ) {
	if ( obj == node_value ) {
		return this;
	} else if ( obj < node_value ) {
		return (left_tree == nullptr) ? nullptr : left_tree->find( obj );
	} else {
		return ( right_tree == nullptr ) ? nullptr : right_tree->find( obj );
	}
}

// Recursively clear the tree
template <typename Type>
void Search_tree<Type>::Node::clear() {
	if ( left_tree != nullptr ) {
		left_tree->clear();
	}

	if ( right_tree != nullptr ) {
		right_tree->clear();
	}

	delete this;
}

template <typename Type>
bool Search_tree<Type>::Node::insert( Type const &obj, Search_tree<Type>::Node *&to_this ) {
	if ( obj < node_value ) {
		if ( left_tree == nullptr ) {
			left_tree = new Search_tree<Type>::Node( obj, to_this, to_this->previous_node );
				//left tree initialized to take parent as next pointer, and parent's previous as prev pointer 
			
			update_height();

			left_tree->next_node->previous_node = left_tree;	//create connection going back to the left child
			left_tree->previous_node->next_node = left_tree;

			return true;
		} else {
			if ( left_tree->insert( obj, left_tree ) ) {
				update_height();

				balance(to_this);		//if insertion was successful (returned true) 
										//call balance function on parent, to see type of balance needed if any and implement it
				return true;
			} else {
				return false;
			}
		}
	} else if ( obj > node_value ) {
		if ( right_tree == nullptr ) {
			right_tree = new Search_tree<Type>::Node( obj, to_this->next_node, to_this );
				//right tree initialized to take parent's next pointer as next pointer, and parent as prev pointer
			update_height();

			right_tree->next_node->previous_node = right_tree;		//create connection going back to the right child
			right_tree->previous_node->next_node = right_tree;

			return true;
		} else {
			if ( right_tree->insert( obj, right_tree ) ) {
				update_height();

				balance(to_this);		//if insertion was successful (returned true) 
										//call balance function on parent, to see type of balance needed if any and implement it
				return true;
			} else {
				return false;
			}
		}
	} else {
		return false;
	}
}

template <typename Type>
bool Search_tree<Type>::Node::erase( Type const &obj, Search_tree<Type>::Node *&to_this ) {
	if ( obj < node_value ) {
		if ( left_tree == nullptr ) {
			return false;
		} else {
			if ( left_tree->erase( obj, left_tree ) ) {
				update_height();

				balance(to_this);		//if erase was successful (returned true) 
										//call balance function on parent, to see type of balance needed if any and implement it
				return true;
			}

			return false;
		}
	} else if ( obj > node_value ) {
		if ( right_tree == nullptr ) {
			return false;
		} else {
			if ( right_tree->erase( obj, right_tree ) ) {
				update_height();
				
				balance(to_this);		//if erase was successful (returned true) 
										//call balance function on parent, to see type of balance needed if any and implement it				
				return true;
			}

			return false;
		}
	} else {
		assert( obj == node_value );	//node is found:

		if ( is_leaf() ) {

			previous_node->next_node = next_node;			//set previous and next nodes' pointers to point to each other
			next_node->previous_node = previous_node;

			to_this = nullptr;
			delete this;
		} else if ( left_tree == nullptr ) {
			
			previous_node->next_node = next_node;			//set previous and next nodes' pointers to point to each other
			next_node->previous_node = previous_node;

			to_this = right_tree;
			delete this;
		} else if ( right_tree == nullptr ) {
			
			previous_node->next_node = next_node;			//set previous and next nodes' pointers to point to each other
			next_node->previous_node = previous_node;
			
			to_this = left_tree;
			delete this;
		} else {	//full node
			node_value = right_tree->front()->node_value;
			right_tree->erase( node_value, right_tree );	//recursively calls erase so no node is actually erased here -> linked list order stays intact
			update_height();
		}

		return true;
	}
}

/*****************************************
 * balances the tree if node is unbalanced, and type of balance depends on
 * left-left, left-right, right-left, right-right imbalance. Takes in parameter
 * with the current node, which balance is called on
 *****************************************/
template <typename Type>
void Search_tree<Type>::Node::balance( Search_tree<Type>::Node *&curr_node ) {

	curr_node -> update_height();	//update height for accuracy, and balance factor calc

	if ( curr_node->check_balance() < -1 ){		//check if left tree is unbalanced

		if ( curr_node->left_tree->check_balance() > 0 ) rotate_left( curr_node -> left_tree ); 	//if type of imbalance is left-right, do a left rotation to get it into left-left

		rotate_right (curr_node);	//do a right rotation on left-left tree to balance

	} else if ( curr_node->check_balance() > 1 ){		//check if right tree is unbalanced
		
		if ( curr_node->right_tree->check_balance() < 0 ) rotate_right( curr_node -> right_tree ); 	//if type of imbalance is right-left, do a right rotation to get it into right-right

		rotate_left (curr_node);	//do a left rotation on right-right tree to balance

	}

	if ( curr_node -> right_tree != nullptr ) curr_node -> right_tree -> update_height();	//update height on right child if right child not empty

	if ( curr_node -> left_tree != nullptr ) curr_node -> left_tree -> update_height();		//update height on left child if left child not empty

	curr_node -> update_height();	//update height after balancing is done

}

/*****************************************
 * helper rotate left function that takes in current node as parameter
 * which: makes the right child a parent, and makes the old parent the 
 * left child of the new parent
 *****************************************/
template <typename Type>
void Search_tree<Type>::Node::rotate_left( Search_tree<Type>::Node *&curr_node ) {

	auto tmp = curr_node->right_tree;			//store right child of curr_node into tmp
	curr_node->right_tree = tmp->left_tree;		//copy left child of tmp into right child of curr_node
	tmp->left_tree = curr_node;					//demote curr_node to left child of tmp
	curr_node = tmp;							//promote tmp to curr_node's parent

}

/*****************************************
 * helper rotate right function that takes in current node as parameter
 * which: makes the left child a parent, and makes the old parent the 
 * right child of the new parent
 *****************************************/
template <typename Type>
void Search_tree<Type>::Node::rotate_right( Search_tree<Type>::Node *&curr_node ) {

	auto tmp = curr_node->left_tree;			//store left child of curr_node into tmp
	curr_node->left_tree = tmp->right_tree;		//copy right child of tmp into left child of curr_node
	tmp->right_tree = curr_node;				//demote curr_node to right child of tmp
	curr_node = tmp;							//promote tmp to curr_node's parent

}

/*****************************************
 * returns a "balance factor" for any node/tree it is called on
 * in an integer format, which describes how imbalanced a tree
 * is; < -1: more nodes on left; >1: more nodes on right 
 *****************************************/
template <typename Type>
int Search_tree<Type>::Node::check_balance() {

	return ( ( (right_tree != nullptr) ? right_tree->height()+1 : 0 ) 
				- ( (left_tree != nullptr) ? left_tree->height()+1 : 0 ) );

}

//////////////////////////////////////////////////////////////////////
//                   Iterator Private Constructor                   //
//////////////////////////////////////////////////////////////////////

template <typename Type>
Search_tree<Type>::Iterator::Iterator( Search_tree<Type> *tree, typename Search_tree<Type>::Node *starting_node ):
containing_tree( tree ),
current_node( starting_node ) {
	// This is done for you...
	// Does nothing...
}

//////////////////////////////////////////////////////////////////////
//                 Iterator Public Member Functions                 //
//////////////////////////////////////////////////////////////////////

template <typename Type>
Type Search_tree<Type>::Iterator::operator*() const {
	// This is done for you...
	return current_node->node_value;
}

template <typename Type>
typename Search_tree<Type>::Iterator &Search_tree<Type>::Iterator::operator++() {
	// Update the current node to the node containing the next higher value
	// If we are already at end do nothing

	// Your implementation here, do not change the return value

	if (current_node->next_node == nullptr) return *this;		//if at end of linked list, don't iterate forward

	current_node = current_node->next_node;						//iterate onto next element of linked list

	return *this;
}

template <typename Type>
typename Search_tree<Type>::Iterator &Search_tree<Type>::Iterator::operator--() {
	// Update the current node to the node containing the next smaller value
	// If we are already at either rend, do nothing

	// Your implementation here, do not change the return value

	if (current_node->previous_node == nullptr) return *this;		//if at start of linked list, don't iterate backward

	current_node = current_node->previous_node;						//iterate onto previous element of linked list

	return *this;
}

template <typename Type>
bool Search_tree<Type>::Iterator::operator==( typename Search_tree<Type>::Iterator const &rhs ) const {
	// This is done for you...
	return ( current_node == rhs.current_node );
}

template <typename Type>
bool Search_tree<Type>::Iterator::operator!=( typename Search_tree<Type>::Iterator const &rhs ) const {
	// This is done for you...
	return ( current_node != rhs.current_node );
}

//////////////////////////////////////////////////////////////////////
//                            Friends                               //
//////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Search_tree<T> const &list ) {
	out << "not yet implemented";

	return out;
}

#endif
