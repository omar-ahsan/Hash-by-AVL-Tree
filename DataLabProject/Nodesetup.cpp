#include "hashbyAVL.h"
#include <iostream>
using namespace std;

Node::Node()
{
	value = 0;
	left = right = NULL;
}

Node::Node(int data)
{
	value = data;
	left = right = NULL;
}

Node::~Node()
{
	delete left;
	delete right;
}
