#include "BST.h"

//!  BSTNode implements a binary search tree node

	//!  Constructor
	BSTNode::BSTNode(const std::string & v) :
	  value(v), left(NULL), right(NULL)
	{
		// Sounds good to me
		return;
	}
	
	//! Copy Constructor DEEP COPY and does not free memory
	BSTNode::BSTNode(const BSTNode & other):
	  value(other.value), left(NULL), right(NULL)
	{
		// Recurse me! Yay!
		value = other.value;
		if (other.left)
			left = new BSTNode(*(other.left));
		if (other.right)
			right = new BSTNode(*(other.right));
		return;
	}
	
	//! Delete Destructor frees memory
	BSTNode::~BSTNode()
	{
		Clear();
		return;
	}

	void BSTNode::Clear()
	{
		if (left) {
			delete left;
			left = NULL;
		}
		if (right) {
			delete right;
			right = NULL;
		}
		return;
	}
	
	void BSTNode::Copy(const BSTNode & other)
	{
		// Recurse me! Yay!
		value = other.value;
		if (other.left)
			left = new BSTNode(*(other.left));
		if (other.right)
			right = new BSTNode(*(other.right));
		return;
	}

	//! Insert string into tree with sort by comparison
	BSTNode * BSTNode::Insert(const std::string & v)
	{
		if (NULL == &v || Find(v))
			return NULL;

		// Greater to the right
		if (0 < value.compare(v))
			if (NULL == right)
				return right = new BSTNode(v);
			else
				return right->Insert(v);
		// Lesser to the left
		else if (0 > value.compare(v))
			if (NULL == left)
				return left = new BSTNode(v);
			else
				return left->Insert(v);
		// Same??? Can't happen
		else
			return NULL;
	}

	//! Find string in tree with sort by comparison
	BSTNode * BSTNode::Find(const std::string & v)
	{
		// Equal means this
		if (0 == value.compare(v))
			return this;

		// Greater to the right
		else if (0 < value.compare(v) && NULL != right)
			return right->Find(v);

		// Lesser to the left
		else if (0 > value.compare(v) && NULL != left)
			return left->Find(v);
		
		// Nothing matches
		return NULL;
	}

	//!  Read-only public methods for use by clients of the BST class
	const std::string & BSTNode::GetValue()
	{
	  return value;
	}

	BSTNode * BSTNode::GetLeft()const
	{
	  return left;
	}

	BSTNode * BSTNode::GetRight()const
	{
	  return right;
	}
	
	//! Assignment operator makes a DEEP COPY and does not free memory
	BSTNode & BSTNode::operator=(const BSTNode & other)
	{
		if (this == &other)
			return *this;
		
		Clear();
		Copy(other);
		
		return *this;
	}


//!  BST implements a binary search tree

	//!  No-arg constructor.  Initializes an empty BST
	BST::BST() : 
		root(NULL), size(0)
	{
		// Empty as can be
		return;
	}


	//!  Copy constructor.  Makes a complete copy of its argument
	BST::BST(const BST & other)
	{
		Copy(other);
		return;
	}
	
	//!  Copy method.  Makes a complete copy of its argument
	void BST::Copy(const BST & other)
	{
		if (this == &other)
			return;
		
		size = other.GetSize();	
		if(other.root)
			root = (new BSTNode(*(other.root)));
		else
			root=NULL;
		
		return;
	}

	//!  Destructor
	BST::~BST()
	{
		Clear();
		return;
	}


	//!  Assignment operator.  Makes a complete copy of its argument
	//!  @return Reference to oneself
	BST & BST::operator=(const BST & other)
	{
		if (this == &other)
			return *this;
			
		Clear();
		Copy(other);
		return *this;
	}


	//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
	//!  @note This is useful for BST clients that need to traverse the tree.)
	BSTNode * BST::GetRoot()const
	{
		return root;
	}


	//!  @return true if the BST is empty, or false if the BST is not empty
	bool BST::IsEmpty() const
	{
		return (NULL == root);
	}


	//!  Removes all values from the BST
	void BST::Clear()
	{
		size = 0;
		if (root)
			delete root;
		root = NULL;
		return;
	}


	//!  @return the number of values in the BST
	int BST::GetSize() const
	{
		return size;
	}


	//!  Inserts value v into the BST
	//!  
	//!  @param v The new value being inserted
	//!
	//!  @return a pointer to the newly inserted node, or NULL if v was already
	//!          in the tree (i.e., NULL is used to indicate a duplicate insertion)
	BSTNode * BST::Insert(const std::string & v) 
	{
		if (Find(v))
			return NULL;

		++size;
		if (root)
			return root->Insert(v);
		else
			return root = new BSTNode(v);
	}


	//!  Searches the tree for value v
	//!  
	//!  @param v The new value being searched for
	//!
	//!  @return a pointer to the node containing v, or NULL if v is not in the tree
	BSTNode * BST::Find(const std::string & v) const
	{
		if (NULL == root)
			return NULL;
		else
			return root->Find(v);
	}


	//! @NOTE: YOU ARE NOT REQUIRED TO IMPLEMENT THE Remove METHOD BELOW
	//!        (BUT YOU CAN IF YOU WANT TO)
	//!
	//!  Removes value v from the tree
	//!  
	//!  @param v The value being removed from the tree
	//!
	//!  @return true if v was removed from the tree, or false if v was not in the tree
	//bool Remove(const std::string & v);
