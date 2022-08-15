namespace Data_structures {
	template <typename Type>
	class Simple_tree {
	    private:
	        Type element;
	        Simple_tree *parent_node;
	        ece250::Single_list<Simple_tree *> children;

	    public:
	        Simple_tree( Type const &, Simple_tree * = 0 );

	        Type retrieve() const;
	        int degree() const;
	        bool is_root() const;
	        bool is_leaf() const;
	        Simple_tree *parent() const;
	        Simple_tree *child( int n ) const;
		void depth_first_traversal() const;

	        void insert( Type const & );
	        void insert( Simple_tree * );
	        void detach();
	};

	template <typename Type>
	Simple_tree<Type>::Simple_tree( Type const &obj, Simple_tree *p ):
	element( obj ),
	parent_node( p ) {
	    // Empty constructor
	}

	template <typename Type>
	Type Simple_tree<Type>::retrieve() const {
	    return element;
	}

	template <typename Type>
	int Simple_tree<Type>::degree() const {
	    return children.size();
	}

	template <typename Type>
	bool Simple_tree<Type>::is_root() const {
	    return ( parent_node == 0 );
	}

	template <typename Type>
	bool Simple_tree<Type>::is_leaf() const {
	    return ( degree() == 0 );
	}

	template <typename Type>
	Simple_tree<Type> *Simple_tree<Type>::parent() const {
	    return parent_node;
	}

	template <typename Type>
	Simple_tree<Type> *Simple_tree<Type>::child( int n ) const {
	    if ( n < 0 || n >= degree() ) {
	        return 0;
	    }

	    ece250::Single_node<Simple_tree *> *ptr = children.head();

	    for ( int i = 1; i < n; ++i ) {
	        ptr = ptr->next();
	    }

	    return ptr->retrieve();
	}

	template <typename Type>
	void Simple_tree<Type>::size() const {
		int s = 1;

		for ( ece250::Single_node<Simple_tree *> *ptr = children.head(); ptr != 0; ptr = ptr->next() ) {
			s += ptr->retrieve()->size();
		}

		return s;
	}

	template <typename Type>
	void Simple_tree<Type>::height() const {
		int h = 0;

		for ( ece250::Single_node<Simple_tree *> *ptr = children.head(); ptr != 0; ptr = ptr->next() ) {
			h = std::max( h, 1 + ptr->retrieve()->height() );
		}

		return h;
	}

	template <typename Type>
	void Simple_tree<Type>::insert( Type const &obj ) {
	    children.push_back( new Simple_tree( obj, this ) );
	}

	template <typename Type>
	void Simple_tree<Type>::insert( Simple_tree<Type> *tree ) {
	    if ( !tree->is_root() ) {
	        tree->detach();
	    }

	    tree->parent_node = this;
	    children.push_back( tree );
	}

	template <typename Type>
	void Simple_tree<Type>::detach() {
	    if ( parent_node == 0 ) {
	        return;
	    }

	    parent_node->children.erase( this );
	    parent_node = 0;
	}

	template <typename Type>
	void Simple_tree<Type>::depth_first_traversal() const {
		std::cout << retrieve() << ' ';

		for (
			ece250::Single_node<Simple_tree *> *ptr = children.head();
			ptr != 0;
			ptr = ptr->next()
		) {
			ptr->retrieve()->depth_first_traversal();
		}
	}
}
