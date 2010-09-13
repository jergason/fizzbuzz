#include <string>
#include <iostream>
#include <set>
#include <list>
#include <algorithm>
#include <vector>
#include <time.h>

#include "tut/tut.hpp"
#include "BST.h"

#define NULL_NODE (static_cast<BSTNode*>(NULL))

using namespace std;

bool gDoRemove = false;
extern std::string gCurrentTest;

string generateKey();
void CheckSubTreeOrder(BSTNode * bNode, bool isLeftLess);
void CheckBSTOrder(BST & bst);
void CompareSubTrees(BSTNode* subTree1, BSTNode* subTree2);
void CompareTrees(BST & bst1, BST & bst2);

struct BSTTest
{
public:
	BSTTest() : BSTTestSize(6379)
	{
	}

	void initBST(BST& bst)
	{
		for(int i = 0; i < BSTTestSize; ++i)
		{
			string key = generateKey();
			if(chosen.find(key) != chosen.end())
			{
				--i;
			}
			else
			{
				chosen.insert(key);
				BSTNode * curNode = bst.Insert(key);
				tut::ensure("Insert() - Return NULL when the value was not in the tree", curNode != NULL);
				tut::ensure_equals("Insert() - Returned a value which was different from the one entered", curNode->GetValue(), key);
				tut::ensure_equals("Insert() - The size of the BST is not the size of the elements inserted", bst.GetSize(), (int)chosen.size());

				curNode = bst.Insert(key);
				tut::ensure_equals("Instert() - Did not return NULL when the value was in the tree", curNode, NULL_NODE);
				tut::ensure_equals("Insert() - Size incremented on duplicate insertion", bst.GetSize(), (int)chosen.size());
			}
		}
	}

	std::string generateKey()
	{
		char key[9];
		int digit = '9'-'0'+1;
		int upCase = 'Z'-'A'+digit+1;
		int top = 'z'-'a'+upCase+1;
		for(int i = 0; i < 9; i++){
			int val = rand()%top;
			if(val < digit){
				key[i] = val + '0';
			}
			else if(val < upCase){
				key[i] = val - digit + 'A';
			}
			else{
				key[i] = val - upCase + 'a';
			}
		}//end for i
		string result(key);
		return result;
	}

	const int BSTTestSize;
	set<string> chosen;
};


void CheckSubTreeOrder(BSTNode * bNode, bool isLeftLess){
	if(bNode != NULL){
		string val = bNode->GetValue();
		BSTNode * lNode = bNode->GetLeft();
		BSTNode * rNode = bNode->GetRight();
		if(isLeftLess){
			if(lNode != NULL){
				tut::ensure("The left node had a greater value when it should have been less", lNode->GetValue() <= val);
				CheckSubTreeOrder(lNode, isLeftLess);
			}
			if(rNode != NULL){
				tut::ensure("The right node had a lesser value when it should have been less", rNode->GetValue() >= val);
				CheckSubTreeOrder(rNode, isLeftLess);
			}
		}
		else{
			if(lNode != NULL){
				tut::ensure("The left node had a lesser value when it should have been less", lNode->GetValue() >= val);
				CheckSubTreeOrder(lNode, isLeftLess);
			}
			if(rNode != NULL){
				tut::ensure("The right node had a greater value when it should have been less", rNode->GetValue() <= val);
				CheckSubTreeOrder(rNode, isLeftLess);
			}
		}
	}
}

void CheckBSTOrder(BST & bst){
	BSTNode * bNode = bst.GetRoot();
	if(bNode != NULL){
		bool isLeftLess = true;
		BSTNode * left = bNode->GetLeft();
		if(left != NULL){
			if(left->GetValue() > bNode->GetValue()){
				isLeftLess = false;
			}
		}
		else{
			BSTNode * right = bNode->GetRight();
			if(right != NULL){
				if(right->GetValue() < bNode->GetValue()){
					isLeftLess = false;
				}
			}
		}
		CheckSubTreeOrder(bNode->GetLeft(), isLeftLess);
		CheckSubTreeOrder(bNode->GetRight(), isLeftLess);
	}
}

void CompareSubTrees(BSTNode* subTree1, BSTNode* subTree2){
	tut::ensure_not("SubTrees are not equal", (subTree1 && !subTree2) || (subTree2 && !subTree1));
	if(subTree1 != NULL){
		tut::ensure_not("Nodes point to the same memory", subTree1 == subTree2 || subTree1 == subTree2);
		tut::ensure_equals("Node values are not equal", subTree1->GetValue(), subTree2->GetValue());
		CompareSubTrees(subTree1->GetLeft(),subTree2->GetLeft());
		CompareSubTrees(subTree1->GetRight(),subTree2->GetRight());
	}
}

void CompareTrees(BST & bst1, BST & bst2){
	tut::ensure_equals("Sizes of the two trees are not equal", bst1.GetSize(), bst2.GetSize());
	CompareSubTrees(bst1.GetRoot(), bst2.GetRoot());
}

namespace tut
{
	namespace
	{
		typedef tut::test_group<BSTTest> tGroup;
		typedef tGroup::object tObject;
		tGroup group("BST");
	}

	template<>
	template<>
	void tObject::test<1> ()
	{
		set_test_name("Default Constructor");
		gCurrentTest = get_test_name();
		BST bst;

		// Root should be NULL
		tut::ensure_equals("Default Constructor - Root is not NULL", bst.GetRoot(), NULL_NODE);

		// Size should be 0
		tut::ensure_equals("Default Constructor - Size is not 0", bst.GetSize(), 0);
		tut::ensure("Default Constructor - Says it's not empty", bst.IsEmpty());
	}

	template<>
	template<>
	void tObject::test<2> ()
	{
		set_test_name("Insert");
		gCurrentTest = get_test_name();
		BST bst;
		initBST(bst);

		CheckBSTOrder(bst);
	}

	template<>
	template<>
	void tObject::test<3> ()
	{
		set_test_name("GetSize");
		gCurrentTest = get_test_name();
		BST bst;
		initBST(bst);
		tut::ensure_equals("GetSize() - The size of the BST is not the size of the elements inserted", bst.GetSize(), static_cast<int>(chosen.size()));
	}

	template<>
	template<>
	void tObject::test<4> ()
	{
		set_test_name("Find");
		gCurrentTest = get_test_name();
		BST bst;
		initBST(bst);

		set<string>::iterator iter;
		for(iter = chosen.begin(); iter != chosen.end(); iter++){
			BSTNode * curNode = bst.Find(*iter);
			tut::ensure("Find() - Node not found when it should have been", curNode != NULL);
			tut::ensure_equals("Find() - Returned a node with the wrong value", curNode->GetValue(), *iter);
		}

		for(int i = 0; i < BSTTestSize; i++){
			string key = generateKey();
			if(chosen.find(key) == chosen.end()){
				BSTNode * curNode = bst.Find(key);
				tut::ensure("Find() - Returned a node when the value was not in the tree", curNode == NULL);
			}
			else{
				--i;
			}
		}
	}

	template<>
	template<>
	void tObject::test<5> ()
	{
		set_test_name("Copy Constructor");
		gCurrentTest = get_test_name();
		BST bst;
		BST emptyCopyBst(bst);
		initBST(bst);

		BST fullCopyBst(bst);
		CompareTrees(bst,fullCopyBst);
	}

	template<>
	template<>
	void tObject::test<6> ()
	{
		set_test_name("Assignment Operator");
		gCurrentTest = get_test_name();
		BST bst;

		//Assign empty to empty
		BST emptyBst;
		emptyBst = bst;
		CompareTrees(bst,emptyBst);

		//Return type check
		tut::ensure ("Assignment Operator: Testing return value", &emptyBst == &(emptyBst = bst));

		//Assign empty to full
		initBST(bst);
		BST fullBst;
		fullBst = bst;
		CompareTrees(bst,fullBst);

		//Assign to self
		fullBst = fullBst;

		//Assign full to empty
		BST& nowEmpty = fullBst;
		nowEmpty = emptyBst;
		CompareTrees(emptyBst, nowEmpty);
	}

	template<>
	template<>
	void tObject::test<7> ()
	{
		set_test_name("Clear");
		gCurrentTest = get_test_name();
		BST bst;
		initBST(bst);

		BST bst2(bst);

		BST bst3;
		bst3 = bst;

		bst.Clear();
		CompareTrees(bst3, bst2);
		bst3.Clear();

		BSTNode* curNode = bst.GetRoot();
		tut::ensure_equals("GetRoot() - Returned a node after the tree was cleared", curNode, NULL_NODE);
	}

	template<>
	template<>
	void tObject::test<8> ()
	{
		set_test_name ("IsEmpty");
		gCurrentTest = get_test_name();
		BST bst;
		initBST(bst);

		BST bst2(bst);
		bst = bst2;
		BST bst3;
		bst3 = bst;
		bst.Clear();
		bst3.Clear();

		tut::ensure_not("IsEmpty() - The Tree is not empty", bst2.IsEmpty());
		bst = bst2; //for the remove stage
		bst2.Clear();
		tut::ensure("IsEmpty() - The Tree is Empty", bst2.IsEmpty());
		tut::ensure_equals("GetSize() - The Tree returned a non 0 size after it was cleared", bst2.GetSize(), 0);
	}

#if TEST_BST_REMOVE
	template<>
	template<>
	void tObject::test<9> ()
	{
		set_test_name ("Remove");
		gCurrentTest = get_test_name();
		if(!gDoRemove)
			return;

		set<string>::iterator iter;
		BSTNode * curNode;

		BST bst;
		initBST(bst);

		BST bst2(bst);
		bst = bst2;
		BST bst3;
		bst3 = bst;
		bst.Clear();
		bst3.Clear();

		bst = bst2;
		bst2.Clear();

		for(int i = 0; i < BSTTestSize; i++){
			string key = generateKey();
			if(chosen.find(key) == chosen.end()){
				ensure_not("Remove() - Returned true when the value was not in the tree", bst.Remove(key));
			}
			else{
				--i;
			}
		}

		BSTNode * root = bst.GetRoot();
		chosen.erase(root->GetValue());
		bst.Remove(root->GetValue());
		root = NULL;

		vector<string> randomv(chosen.begin(), chosen.end());
		random_shuffle(randomv.begin(), randomv.end());

		for(vector<string>::iterator vIter = randomv.begin(); vIter != randomv.end(); vIter++){
			ensure("Remove() - Returned false whe nthe value was in the tree", bst.Remove(*vIter));
			ensure_not("Remove() - Returned true when the value was not in the tree", bst.Remove(*vIter));

		}
		ensure_equals("Remove() - Size of tree is not 0 after removing all values", bst.GetSize(), 0);
		ensure_equals("GetRoot() - Did not return NULL after removing all values", bst.GetRoot(), NULL_NODE);
	}
#endif
}
