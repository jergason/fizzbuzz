#include "BST.h"
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>

int main(int argc, char * argv[]) {
	std::string str;
	str.append("AJ");
	std::cout << "okay" << std::endl;
	BST * bst = new BST();
	bst->Insert(str);
	std::cout << bst->GetRoot()->GetValue() << std::endl;
	BST * bstCopy = new BST(*bst);
	std::cout << bstCopy->GetRoot()->GetValue() << std::endl;
}
