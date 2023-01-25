#include "hashbyAVL.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

int main()
{
    AVL_table tree;
    int x = 300, y = 300;
    cout << "Making AVL TREE with hash table 0-9" << endl;
    for (int i = 0; i < 10; i++)
    {
        Node* new_Node = new Node();
        new_Node->value = i;
        tree.root = tree.insert(tree.root, new_Node, x, y);
    }
    tree.Display(tree.root);
    cout << endl;


}
