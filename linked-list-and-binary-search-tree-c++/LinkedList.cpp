#include "LinkedList.h"

//! LLNode implements a doubly-linked list node
	//!  Constructor
	LLNode::LLNode(const std::string & v, LLNode * p, LLNode * n) :
	  value(v), prev(p), next(n)
	{
		// Good enough
		return;
	}
	
	//! Copy Constructor SHALLOW COPY and does not free memory
	//!Feel free to change this function(IE, to a deep copy).
	LLNode::LLNode(const LLNode & other)
	{
		if (this == &other)
			return;

		// It makes sense (in my mind) for this to be shallow and disconnected
		value = other.value;
		prev = NULL; //other.prev;
		next = NULL; //other.next;
	}

	//!  Read-only public methods for use by clients of the LinkedList class
	const std::string & LLNode::GetValue() const
	{
	  return value;
	}


	LLNode * LLNode::GetPrevious() const
	{
	  return prev;
	}


	LLNode * LLNode::GetNext() const
	{
	  return next;
	}
	
	//! Assignment operator makes a SHALLOW COPY and does not free memory
	//!Feel free to change this function(IE, to a deep copy).
	LLNode & LLNode::operator=(const LLNode & other)
	{
		if(this != &other)
		{
			value = other.value;
			prev = other.prev;
			next = other.next;
		}
		return *this;
	}









//! LinkedList implements a doubly-linked list

	//!  No-arg constructor.  Initializes an empty linked list
	LinkedList::LinkedList()
	{
		length = 0;
		head = NULL;
		return;	
	}


	//!  Copy constructor.  Makes a complete copy of its argument
	LinkedList::LinkedList(const LinkedList & other)
	{
		Copy(other);
		return;
	}

	//! Copy make a DEEP copy.  Makes a complete copy of its argument
	void LinkedList::Copy(const LinkedList & other)
	{
		if (this == &other)
			return;
		if (NULL == other.head) {
			head = NULL;
			return;
		}

		LLNode * tmpCopy = NULL;
		LLNode * oHead = NULL;

		length = other.GetSize();
		oHead = other.head;

		head = new LLNode(*oHead);
		oHead = oHead->next;
		tmpCopy = head;
		while (oHead != NULL) {
			tmpCopy->next = new LLNode(*oHead);
			tmpCopy->next->prev = tmpCopy;
			tmpCopy = tmpCopy->next;
			oHead = oHead->next;
		}
	}

	//!  Destructor
	LinkedList::~LinkedList()
	{
		Clear();
	}

	//! Assignment operator.  Makes a complete copy of its argument
	//! @return A reference to oneself
	LinkedList& LinkedList::operator =(const LinkedList & other)
	{
		if (this == &other)
			return *this;

		Clear();
		Copy(other);
		return *this;
	}


	//!  @return true if the list is empty, or false if the list is not empty
	bool LinkedList::IsEmpty() const
	{
		return (0 == length);
	}


	//!  Removes all values from the list
	void LinkedList::Clear() {
		LLNode * tmpCopy = NULL;
		if (NULL == head)
			return;

		///*
		while (NULL != head) {
			tmpCopy = head;
			head = head->next;
			delete tmpCopy;
		}//*/

		length = 0;
		head = NULL;
		return;
	}


	//!  @return the number of values in the list
	int LinkedList::GetSize() const
	{
		return length;
	}



	//!  @return a pointer to the first node in the list, or NULL if the list is empty
	LLNode * LinkedList::GetFirst()const
	{
		return head;
	}



	//!  @returns a pointer to the last node in the list, or NULL if the list is empty
	LLNode * LinkedList::GetLast()const
	{
		if (IsEmpty())
			return NULL;
		
		LLNode * tail;
		tail = head;
		while (NULL != tail->next) {
			tail = tail->next;
		}
		return tail;
	}


	//!  Inserts value v into the list after node n
	//!  
	//!  @param v The new value being inserted
	//!  @param n A node that is already in the list after which the new node should 
	//!      be inserted.
	//!      If n is NULL, the new node should be inserted at the beginning of the list.
	//!
	//!  @return a pointer to the newly inserted node
	LLNode * LinkedList::Insert(const std::string & v, LLNode * n)
	{
		if (NULL == &v || Find(v, NULL))
			return NULL;

		++length;

		LLNode * tmpCopy;

		if (NULL == n) {
			tmpCopy = new LLNode(v, NULL, NULL);
			if (NULL != head)
				head->prev = tmpCopy;
			tmpCopy->next = head;
			return head = tmpCopy;
		}

		tmpCopy = new LLNode(v, n, n->next);
		if (NULL != n->next)
			n->next->prev = tmpCopy;
		tmpCopy->prev = n;
		tmpCopy->next = n->next;
		n->next = tmpCopy;
		
		return tmpCopy;
	}


	//! Searches for the first occurrence of value v that appears in the list 
	//!   after node n
	//!   
	//!  @param v The value being searched for
	//!  @param n The node in the list after which the search should begin.
	//!      If n is NULL, the list should be searched from the beginning.
	//!
	//!  @return a pointer to the node containing v, or NULL if v is not found
	LLNode * LinkedList::Find(const std::string & v, LLNode * n) const
	{
		LLNode * result;
		if (NULL != n)
			result = n->next;
		else
			result = head;

		while (NULL != result) {
			if (0 == result->value.compare(v))
				return result;
			result = result->next;
		}

		return result;
	}


	//!  Removes node n from the list
	//!  
	//!  @param n The node being removed from the list
	void LinkedList::Remove(LLNode * n)
	{
		if (NULL == n)
			return;

		--length;

		if (NULL != n->prev)
			n->prev->next = n->next;
		else {
			head = n->next; // Could be NULL
			if (NULL != head)
				head->prev = NULL;
		}
		if (NULL != n->next)
			n->next->prev = n->prev;

		delete n;
		n = NULL;

		return;
	}

