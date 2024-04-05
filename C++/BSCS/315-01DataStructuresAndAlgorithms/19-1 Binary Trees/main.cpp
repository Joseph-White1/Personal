#include<iostream>
#include "binaryTree.h"
#include "binarySearchTree.h"

using namespace std;

int main()
{
    //class has virtual methods so a pointer of the type base class is created and initialized with the address of the derived class object
    binaryTreeType<int> *binTree;
    bSearchTreeType<int> seaTree;
    binTree = &seaTree;

    binTree->insert(23);
    binTree->insert(13);
    binTree->insert(223);
    binTree->insert(2);
    binTree->insert(3);
    binTree->insert(123);
    binTree->insert(43);
    binTree->insert(6);

    cout << "Number of nodes in the binary tree: " << binTree->treeNodeCount() << endl;

    return 0;
}
