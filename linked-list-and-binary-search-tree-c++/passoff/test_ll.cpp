#include <string>
#include <iostream>
#include <set>
#include <list>
#include <algorithm>
#include <vector>
#include <time.h>

#include "tut/tut.hpp"
#include "LinkedList.h"

#define NULL_NODE (static_cast<LLNode*>(NULL))

using namespace std;

bool gDoSmall = true;
extern std::string gCurrentTest;

string generateKey();
void CompareLists(const LinkedList & aList, list<string> & master);

struct LinkedListTest
{
public:
	LinkedListTest() : LLTestSize((gDoSmall) ? 2827 : 8239)
	{
		for(int i = 0; i < LLTestSize; ++i)
		{
			string key = generateKey();
			if(chosen.find(key) != chosen.end())
			{
				--i;
			}
			else
			{
				master.push_back(key);
				chosen.insert(key);
			}
		}
	}

	void initList (LinkedList& aList)
	{
		list<string>::iterator iter;
		for(iter = master.begin(); iter != master.end(); ++iter)
		{
			LLNode* curNode = aList.Insert(*iter, NULL);
			tut::ensure ("Insert() - The returned node is NULL", curNode != NULL_NODE);
			tut::ensure_equals ("Insert() - The returned node had the wrong value", curNode->GetValue(), *iter);
		}
	}

	void sortedInitList (LinkedList& aList)
	{
		aList.Clear();
		int count = 0;

		list<string>::iterator iter;
		for(iter = master.begin(); iter != master.end(); ++iter)
		{
			LLNode* curNode = aList.GetLast();
			while(curNode != NULL && 0 < curNode->GetValue().compare(*iter))
			{
				curNode = curNode->GetPrevious();
			}
			aList.Insert(*iter, curNode);

			tut::ensure_equals("Insert() - Size != number of elements inserted", aList.GetSize(), ++count);
		}
	}

	string generateKey()
	{
		static const int kKeyLength = 9;
		char key[kKeyLength];
		for (int i = 0; i < kKeyLength; ++i)
			key[i] = '\0'; 

		int digit = '9'-'0'+1;
		int upCase = 'Z'-'A'+digit+1;
		int top = 'z'-'a'+upCase+1;
		for(int i = 0; i < kKeyLength; ++i)
		{
			int val = rand()%top;
			if(val < digit)
			{
				key[i] = val + '0';
			}
			else if(val < upCase)
			{
				key[i] = val - digit + 'A';
			}
			else
			{
				key[i] = val - upCase + 'a';
			}
		}
		string result(key);
		return result;
	}

	const int LLTestSize;

	set<string> chosen;
	list<string> master;
};

void CompareLists(const LinkedList & aList, list<string> & master){
	const LLNode * curNode = aList.GetFirst();

	list<string>::iterator iter;
	for(iter = master.begin(); iter != master.end() && curNode != NULL; iter++, curNode = curNode->GetNext())
	{
		tut::ensure_equals("GetValue() - The values are not the order which they should be", curNode->GetValue(), *iter);
	}

	tut::ensure_equals("GetNext() - The list is longer than it should be", curNode, NULL_NODE);
	tut::ensure("GetNext() - The list is shorter than it should be", iter == master.end());
}

namespace tut
{
	namespace
	{
		typedef tut::test_group<LinkedListTest> tGroup;
		typedef tGroup::object tObject;
		tGroup group("LinkedList");
	}

	template<>
	template<>
	void tObject::test<1> ()
	{
		set_test_name ("Default Constructor");
		gCurrentTest = get_test_name();

		LinkedList aList;
		tut::ensure_equals("Default Constructor - List size != 0", aList.GetSize(), 0);
		tut::ensure_equals("Default Constructor - first != NULL", aList.GetFirst(), NULL_NODE);
		tut::ensure_equals("Default Constructor - last != NULL", aList.GetLast(), NULL_NODE);
	}

	template<>
	template<>
	void tObject::test<2> ()
	{
		set_test_name ("Clear");
		gCurrentTest = get_test_name();

		LinkedList aList;
		aList.Clear();

		aList.Insert("To Remove", NULL);
		aList.Clear();

		tut::ensure_equals("Clear() - size != 0", aList.GetSize(), 0);
		tut::ensure_equals("Clear() - first != NULL", aList.GetFirst(), NULL_NODE);
		tut::ensure_equals("Clear() - last != NULL", aList.GetLast(), NULL_NODE);
	}

	template<>
	template<>
	void tObject::test<3> ()
	{
		set_test_name ("Basic Insert Tests");
		gCurrentTest = get_test_name();

		LinkedList aList;
		initList(aList);
		master.reverse();
		
		tut::ensure_equals("Insert() - List size != number of strings inserted", aList.GetSize(), static_cast<int>(master.size()));
		
		tut::ensure("GetLast() - List was empty", aList.GetLast() != NULL);
		tut::ensure_equals("GetLast() - Returned the wrong value", aList.GetLast()->GetValue(), master.back());
		tut::ensure_equals("GetLast() - The returned node had a next", aList.GetLast()->GetNext(), NULL_NODE);
		
		tut::ensure("GetFirst() - List was empty", aList.GetFirst() != NULL);
		tut::ensure_equals("GetFirst() - Returned the wrong value", aList.GetFirst()->GetValue(), master.front());
		tut::ensure_equals("GetFirst() - The returned node had a next", aList.GetFirst()->GetPrevious(), NULL_NODE);
	}

	template<>
	template<>
	void tObject::test<4> ()
	{
		set_test_name ("Insert");
		gCurrentTest = get_test_name();

		master.reverse();

		LinkedList aList;
		aList.Clear();

		int count = 0;
		list<string>::iterator iter;
		for(iter = master.begin(); iter != master.end(); iter++)
		{
			LLNode* curNode = aList.GetLast();
			while(curNode != NULL && curNode->GetValue().compare(*iter) > 0)
			{
				curNode = curNode->GetPrevious();
			}
			aList.Insert(*iter, curNode);

			ensure_equals("Size != number of elements inserted", aList.GetSize(), ++count);
		}

		sortedInitList(aList);
		list<string> sorted(master.begin(), master.end());
		sorted.sort();

		tut::ensure_equals("Insert() - Size != Number of strings inserted", aList.GetSize(), static_cast<int>(sorted.size()));

		CompareLists(aList, sorted);
	}

	template<>
	template<>
	void tObject::test<5> ()
	{
		set_test_name ("Copy Constructor");
		gCurrentTest = get_test_name();

		LinkedList aList;
		LinkedList emptyCopy(aList);

		initList(aList);
		master.reverse();
		sortedInitList(aList);

		list<string> sorted(master.begin(), master.end());
		sorted.sort();

		LinkedList fullCopyList(aList);

		tut::ensure_equals("Copy Constructor - Size != size of original list", aList.GetSize(), fullCopyList.GetSize());

		aList.Clear();
		CompareLists(fullCopyList, sorted);
	}

	template<>
	template<>
	void tObject::test<6> ()
	{
		set_test_name ("Assignment Operator");
		gCurrentTest = get_test_name();

		LinkedList aList;

		//Assign an empty to an empty
		LinkedList emptyList;
		emptyList = aList;

		//Return type check
		tut::ensure ("Assignment Operator: Testing return value", &emptyList == &(emptyList = aList));

		//Assign full to an empty
		initList(aList);
		master.reverse();
		sortedInitList(aList);

		list<string> sorted(master.begin(), master.end());
		sorted.sort();

		LinkedList fullList;
		fullList = aList;
		tut::ensure_equals("Assignment Operator - Size != size of original list when going from empty to full", fullList.GetSize(), aList.GetSize());

		aList.Clear();
		CompareLists(fullList, sorted);

		//Self assignment
		fullList = fullList;
		tut::ensure_equals("Assignment Operator - Size != size of original list on self assignment", fullList.GetSize(), sorted.size());
		CompareLists(fullList, sorted);

		//Assign full to empty
		LinkedList& nowEmpty = fullList;
		nowEmpty = aList;
		tut::ensure_equals("Assignment Operator - Size != size of original list when going from full to empty", nowEmpty.GetSize(), aList.GetSize());
	}

	template<>
	template<>
	void tObject::test<7> ()
	{
		set_test_name ("IsEmpty");
		gCurrentTest = get_test_name();

		LinkedList aList;
		initList(aList);
		master.reverse();
		sortedInitList(aList);

		list<string> sorted(master.begin(), master.end());
		sorted.sort();

		LinkedList cList;
		cList = aList;

		tut::ensure_equals("Assignment Operator - Size != size of original list", cList.GetSize(), aList.GetSize());

		aList.Clear();

		CompareLists(cList, sorted);

		tut::ensure_not("IsEmpty() - returned true when list was not empty", cList.IsEmpty());
		tut::ensure("IsEmpty() - returned false when list was empty", aList.IsEmpty());
	}

	template<>
	template<>
	void tObject::test<8> ()
	{
		set_test_name ("Find");
		gCurrentTest = get_test_name();

		LinkedList aList;
		initList(aList);
		master.reverse();

		list<string> sorted(master.begin(), master.end());
		sorted.sort();

		list<string>::iterator iter;
		for(iter = master.begin(); iter != master.end(); iter++){
			LLNode* curNode = aList.Find(*iter, NULL);

			tut::ensure("Find() - Find returned NULL when it shouldn't have", curNode != NULL);
			tut::ensure_equals("Find() - Find returned the wrong value", curNode->GetValue(), *iter);
		}//end for iter

		LLNode* curNode = NULL;
		curNode = aList.Find(master.back(), aList.GetLast());

		tut::ensure_equals("Find() - Find is starting its search on the node given, not the node after the one given", curNode, NULL_NODE);

		curNode = aList.GetFirst();
		int attempt = -1;
		while(curNode != NULL){
			tut::ensure_equals("Find() - Find is returning a value when it should be returning NULL", aList.Find(curNode->GetValue(), curNode), NULL_NODE);
			curNode = curNode->GetNext();
			tut::ensure("GetNext() - Infinite loop hit", attempt++ <= LLTestSize);
		}

		iter = master.begin();
		iter++;
		curNode = aList.Find(*iter, NULL);
		tut::ensure("Find() - Returned NULL when it should not have", curNode != NULL);
		curNode = aList.Find(master.front(), curNode);
		tut::ensure_equals("Find() - Did not return NULL when the item was in the list, but before the search point", curNode, NULL_NODE);

		string key = generateKey();
		while(chosen.find(key) != chosen.end()){
			key = generateKey();
		}
		curNode = aList.Find(key, NULL);
		tut::ensure_equals("Find() - Find is returning a value when the value is not in the list", curNode, NULL_NODE);
	}

	template<>
	template<>
	void tObject::test<9> ()
	{
		set_test_name ("Remove");
		gCurrentTest = get_test_name();

		LinkedList aList;
		initList(aList);

		master.reverse();
		list<string> sorted(master.begin(), master.end());
		sorted.sort();

		for(int i = 0; i < LLTestSize/2; i++)
		{
			ensure_not("Internal Error", master.empty());
			master.pop_back();
			aList.Remove(aList.GetLast());
			ensure_equals("GetSize() Did not return the correct size after a remove", aList.GetSize(), static_cast<int>(master.size()));
		}

		for(set<string>::iterator setIter = chosen.begin(); setIter != chosen.end(); ++setIter)
		{
			LLNode* curNode = aList.Find(*setIter, NULL);
			list<string>::iterator iter = find(master.begin(), master.end(), *setIter);
			ensure("Find() - Returned a value which was removed", iter != master.end() || curNode == NULL);
			ensure("Find() - Returned NULL when the value was in the list", iter == master.end() || curNode != NULL);
			ensure("Find() - Find returned the wrong value", curNode == NULL || curNode->GetValue() == *setIter);
		}

		master.sort();
		list<string>::iterator iter;
		for(iter = master.begin(); iter != master.end(); ++iter)
		{
			aList.Remove(aList.Find(*iter,0));
		}

		ensure_equals("Remove() - List did not return a size of 0 when the list was empty", aList.GetSize(), 0);
		ensure("Remove() - List should be empty", aList.IsEmpty());
		ensure_equals("Remove() - List should have no first node", aList.GetFirst(), NULL_NODE);
		ensure_equals("Remove() - List should have no last node", aList.GetLast(), NULL_NODE);
	}
}

