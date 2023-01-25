#ifndef hashbyAVL_h
#define hashbyAVL_h
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

//NODE CLASS
class Node
{
public:
	//AVL
	int value;
	Node* left;
	Node* right;

	//BST
	int bstvalue;
	Node* bstroot;
	Node* parent;
	Node* bstleft;
	Node* bstright;
	Node* bsthead;

	//SFML circle shape representing a node
	//SFML AVL properties
	sf::CircleShape circle;
	sf::RectangleShape linelink, linelink2;
	sf::Font font;
	sf::Text treedata;

	//SFML BST Properties
	sf::CircleShape bstcircle;
	sf::RectangleShape bstlink, bstlink2;
	sf::RectangleShape connect;
	sf::Text bstdata;




	Node();
	Node(int data);
	~Node();
};


//HASH BY USING AVL (CLASS)
class AVL_table
{
public:
	Node* root;
	Node* bstnode;
	int balfactor;
	//Constructor
	AVL_table();
	//Destructor
	~AVL_table();

	//METHODS

	//AVL
	Node* getRoot();
	Node* insert(Node* rt, Node* new_Node, int x, int y);
	Node* search(Node* rt, int data);
	int THeight(Node* rt);
	int balanceFactor(Node* rt);


	//AVL SFML
	void Display(Node* r);
	void DrawAVLNodes(sf::RenderWindow& Window, Node*& node, int x, int y, int i);
	void printAVL(sf::RenderWindow& Window, Node* root);

	//BST

	//BST Creation
	void BSTinsert(sf::RenderWindow& Window);
	void MatchBST(int modval, int val, Node* r);
	void CreateBST(int modval, int val, Node* bstr);
	//BST Traversal
	void ShowBST(Node* r , int sr);
	void ShowBSTtraverse(Node* s);
	//Single BST Node location
	void FindNode(Node* root, int val, int mod);
	void FindKey(Node* s, int val);
	

	//BST SFML
	void BSTroots(Node* s, sf::RenderWindow& Window);
	void BSTrootsSFML(Node* root, sf::RenderWindow& Window);
	void DrawBSTNodes(Node*& s, int x, int y, sf::RenderWindow& Window);
	void printBST(sf::RenderWindow& Window, Node* root);
};

#endif


