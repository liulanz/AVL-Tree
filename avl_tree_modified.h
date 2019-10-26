// Liulan Zheng
// CSCI 335 Homework 2
// avl tree file for part 2c

#ifndef AVL_TREE__MODIFIED_H
#define AVL_TREE__MODIFIED_H
#include "sequence_map.h"
#include "dsexceptions.h"
#include <math.h>
#include <algorithm>
#include <iostream> 
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS**************************************************
// void insert( x )      					 --> Insert x
// void remove( x )      					 --> Remove x (unimplemented)
// bool contains( x )    					 --> Return true if x is present
// bool find( x, total_calls)				 --> Return true if x is present;
//												 Pass by reference total number of recursion called
// float AverageDepth()     				 --> Return the average depth i.e. Internal path length / number of nodes
// float RatioOfAverageDepthToLog2N()        --> Return ratio of the average depth to (log2 n), where n is total number of nodes
// void findInTree( x ) 					 --> Print the elements of x when x is found; else prints "Not Found"
// Comparable findMin( ) 					 --> Return smallest item
// Comparable findMax( ) 					 --> Return largest item
// boolean isEmpty( )    					 --> Return true if empty; else false
// void makeEmpty( )     					 --> Remove all items
// void printTree( )    					 --> Print tree in sorted order
// int NumberOfNode()       				 --> Return total number of nodes in this tree
// void remove( x, total_calls, success )    --> Remove x from the tree. 
// 	                                             Pass by reference total_calls: total number of recursion called
// 												 Pass by reference success: total number of successful removes
// ******************ERRORS************************************************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
/************************************************ public ***********************************/
  public:
	// Zero parameterized constructor
    AvlTree( ) : root{ nullptr }
      { }
    // copy constructor
    AvlTree( const AvlTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }
	// One parameterized constructor
    AvlTree( AvlTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    // Destructor
    ~AvlTree( )
    {
        makeEmpty( );
    }
	
    /**
     * Deep copy.
     */
    AvlTree & operator=( const AvlTree & rhs )
    {
        AvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
	
    /**
     * Move.
     */
    AvlTree & operator=( AvlTree && rhs )
    {
        std::swap( root, rhs.root );
        
        return *this;
    }
	
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }
	
    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }
	
    /**
     * Return true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }
	
	/**
	 * Return true if x is found in the tree
	 * Passed by reference total_calls : total number of recursion is called 
	 */
	bool find( const Comparable & x, int & total_calls ) const
    {
        return find( x, root, total_calls );
    }
	
	/**
	 * Returns average depth of the tree i.e. internal path length / number of nodes
	 */
	float AverageDepth()
	{
		return AverageDepth(root);
	}
	
	/**
	 * Returns ratio of	the	average	depth to (log2 n), where n is total number of nodes
	 */
	 float RatioOfAverageDepthToLog2N()
	 {
		 return RatioOfAverageDepthToLog2N(root);
	 }
	
	/** 
	 * Print the elements of x when x is found; else prints "Not Found"
	 */
	void findInTree(const Comparable & x)const
	{
		findInTree(x, root);
	}
	
    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }
	
    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }
	
	/**
	 * Return total number of nodes in tree
	 */
	int NumberOfNode()
	{
		return NumberOfNode(root);
	}
	
    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
	
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
     
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }
	
	/**
	 * Remove x from the tree. Nothing is done if x is not found.
	 * Pass by reference total_calls: total number of recursion called
	 * Pass by reference success: total number of successful removes
	 */
	void remove( const Comparable & x, int& total_calls, int &success )
    {
        remove( x, root, total_calls, success);
    }
	
/****************************************** private ***********************************************/
  private:
    struct AvlNode
    {
        Comparable element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;

        AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ ele }, left{ lt }, right{ rt }, height{ h } { }
        
        AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
    };

    AvlNode *root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
		else
			t->element.Merge(x);
        
        balance( t );
    }
	
	/**
	 * t is the node that roots the subtree.
	 * Return internal path length of the tree i.e. D(N) = D(i) + D(N-i-1) + N -1
	 */
	int Depth(AvlNode * &t)
	{
		 if(t == nullptr || (t->left == nullptr && t->right == nullptr))
            return 0;
        else 
            return Depth(t->left) + Depth(t->right) + NumberOfNode(t) - 1; 
	}
	
	/**
	 * t is the node that roots the subtree.
	 * nodes is the total number of nodes on this tree
	 * dep_sum is the internal path length of this tree
	 * Return average depth of this tree i.e. internal path length / total number of nodes
	 */
	float AverageDepth(AvlNode *&t)
	{
		int nodes = NumberOfNode(t);
		int depth_sum =Depth(t);
		return (float)depth_sum/nodes;
	}

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
       
        balance( t );
    }
	
	/**
	 * t is the node that roots the subtree
	 * Return the total number of nodes on this tree
	 */
    int NumberOfNode(AvlNode * & t)
	{
		if(t == nullptr)
			return 0;
		else if(t -> left == nullptr && t -> right == nullptr)
			return 1;
		else
			return NumberOfNode(t->right) + NumberOfNode(t->left)+1;
	}
	
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, AvlNode * & t)
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left);
        else if( t->element < x )
            remove( x, t->right);
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right);
        }
        else
        {
            AvlNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
        
        balance( t );
    }
	
	/**
     * Internal method to remove from a subtree.
     * x is the item to remove.
	 * total_calls (pass by reference) is the total number of remove recursion is called
	 * success (pass by reference) is the total number of successful remove
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
	void remove( const Comparable & x, AvlNode * & t, int& total_calls, int& success)
    {
		total_calls++;
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left, total_calls, success);
        else if( t->element < x )
            remove( x, t->right, total_calls, success);
        else if( t->left != nullptr && t->right != nullptr ) // Two children
		{
            t->element = findMin( t->right )->element;
            remove( t->element, t->right, total_calls, success);
		}
        else
        {	
            AvlNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
			success++;
            delete oldNode;
        }
        balance( t );
    }
    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t )
    {
        if( t == nullptr )
            return;
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ) {
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        } else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ) {
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
		}
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }
    
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }
	
	 /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
	 * Print the elements in x if x is found; else print "Not Found"
     */
	void findInTree(const Comparable & x, AvlNode *t)const
	{
		if( t == nullptr )
            cout<< "Not Found" << endl;
        else if( x < t->element)
            findInTree( x, t->left );
        else if( t->element < x )
            findInTree( x, t->right );
        else
			cout << t->element;	 //Match
	}
	
	/**
	 * t is the node that roots the tree.
	 * Return ratio of the average depth to (log2 n), where n is total number of nodes
	 */
	float RatioOfAverageDepthToLog2N(AvlNode *t)
	{
		return AverageDepth()/log2(NumberOfNode());
	}
	
    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
	
	/**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
	 * total_calls (pass by reference) is the total number of find recursions called
     * t is the node that roots the tree.
     */ 
    bool find( const Comparable & x, AvlNode *t, int & total_calls) const
    {
		total_calls++;
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return find( x, t->left , total_calls);
        else if( t->element < x )
            return find( x, t->right, total_calls );
        else
            return true;    // Match
    }
	
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t ) const
    {
        if( t != nullptr )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
    }
	
        // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height( AvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
		// double rotation
		AvlNode *k1 = k3->left;
		AvlNode *k2 = k1->right;
		k1->right = k2 ->left;
		k2 -> left = k1;
		k3->left = k2->right;
		k2-> right = k3;
		k1 -> height = max(height(k1->left), height(k1->right))+1;
		k3 ->height = max(height(k3->left), height(k3->right))+1;
		k2 ->height = max(k1->height, k3->height) +1;
		k3 = k2;
		
       // double rotation using two single rotations: 
	   //  rotateWithRightChild( k3->left );
       // rotateWithLeftChild( k3 );
		
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
		// double rotation
		AvlNode *k3 = k1 ->right;
		AvlNode *k2 = k3 -> left;
		k1->right = k2 -> left;
		k2 ->left = k1;
		k3 -> left = k2->right;
		k2-> right = k3;
		k1 -> height = max(height(k1->left), height(k1->right))+1;
		k3 ->height = max(height(k3->left), height(k3->right))+1;
		k2 ->height = max(k1->height, k3->height) +1;
		k1 = k2;
		
		// double rotation using two single rotations:
		// rotateWithLeftChild( k1->right );
        // rotateWithRightChild( k1 );
    }
};

#endif
