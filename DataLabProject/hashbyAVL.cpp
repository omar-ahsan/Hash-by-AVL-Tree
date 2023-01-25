#include "hashbyAVL.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
using namespace std;

#define SPACE 10

//Constructor
AVL_table::AVL_table()
{
    balfactor = 0;
    bstnode = NULL;
    root = NULL;
}

//Destructor
AVL_table::~AVL_table()
{
    delete root;
}



//Methods

// Finds Tree Height
int AVL_table::THeight(Node* rt)
{
    if (rt == NULL)
    {
        return -1;
    }
    else
    {
        int leftHeight = THeight(rt->left); // stores count of traversals
        int rightHeight = THeight(rt->right); // stores count of traversals

        if (leftHeight > rightHeight)
        {
            return (leftHeight + 1);
        }
        else
        {
            return (rightHeight + 1);
        }
    }
}


//Balance factor function , uses above function to find the difference between left and right subtree
int AVL_table::balanceFactor(Node* node)
{
    if (node == NULL)
    {
        return -1;
    }
    else
    {
        return THeight(node->left) - THeight(node->right); // returns an int number
    }
}



Node* AVL_table::getRoot()
{
    return root;
}

//Right rotation function
Node* rightRotate(Node* r) {
    Node* a = r->left; // setting a to point to r->left
    Node* b = a->right; // setting b to point to r->right

    a->right = r; // a->right now stores r (initial)
    r->left = b; // r->left now points to b (a->right)

    return a;
}
//Left rotation function
Node* leftRotate(Node* l) {
    Node* a = l->right; // setting a to point to r->right
    Node* b = a->left; //setting b to point to r->left

    a->left = l; // a->left now stores l (initial)
    l->right = b; // l->right now points to b (a->left)

    return a;
}

//AVL insert function , rotation cases referred from stackoverflow.
Node* AVL_table::insert(Node* rt, Node* new_Node, int x, int y)
{
    if (rt == NULL)
    {
        rt = new_Node;
        new_Node->circle.setRadius(17);
        new_Node->circle.setFillColor(sf::Color::Green);
        new_Node->circle.setOutlineColor(sf::Color::Black);
        new_Node->circle.setOutlineThickness(0.95);
        return rt;
    }

    if (new_Node->value > rt->value)
    {
        rt->right = insert(rt->right, new_Node, x + 50, y - 50);
    }
    else if (new_Node->value < rt->value)
    {
        rt->left = insert(rt->left, new_Node, x - 50, y - 50);
    }

    //Checking for BalanceFactor
    balfactor = balanceFactor(rt);
    // For LEFT LEFT Case
    if (balfactor > 1 && rt->left->value > new_Node->value)
    {
        return rightRotate(rt);
    }
    // For RIGHT RIGHT Case
    else if (balfactor < -1 && rt->right->value < new_Node->value)
    {
        return leftRotate(rt);
    }
    // FOR LEFT RIGHT Case
    else if (balfactor > 1 && rt->left->value < new_Node->value)
    {
        rt->left = leftRotate(rt->left);
        return rightRotate(rt);
    }
    // FOR RIGHT LEFT Case
    else if (balfactor < -1 && rt->right->value > new_Node->value)
    {
        rt->right = rightRotate(rt->right);
        return leftRotate(rt);
    }

    return rt;
}


//BST Tree

//Insertion of a bst node
void AVL_table::BSTinsert(sf::RenderWindow& Window)
{
    int invalue;
    int modval;
    cout << "Hash Function is : X % 10" << endl;

    int option = -1;
    if (option != 0)
    {
       
        cout << "1.Insert" << endl;
        cout << "2.Search Node" << endl;
        cout << "3.Search for specific hash key" << endl;
        cin >> option;
        if (option == 1)
        {
            cout << "Enter Value X in hash function : ";
            cin >> invalue;
            modval = invalue % 10;

            MatchBST(modval, invalue, root); // sending modval (x) , invalue (user input value) , root (AVL tree root)
            
        }
        else if (option == 2)
        {
            int sr;
            cout << "Enter Root to Search BST for : ";
            cin >> sr;
            ShowBST(root, sr); // search function for a whole avl node
            cout << endl;
        }
        else if (option == 3)
        {
            int hk;
            cout << "Enter Hash key to search BST : ";
            cin >> hk;
            int modsearch = hk % 10; 
            FindNode(root, hk, modsearch); // sending Avl root , hash key entered by user ,  modsearch (avl 0-9 to locate the corresponding node)
        }
        else if (option == 0)
        {
            return;
        }
    }
}

//Search function for individual key
void AVL_table::FindNode(Node* root, int val, int mod)
{
    if (root == NULL)
    {
        return;
    }

    if (root->value == mod) // finding the avl node using mod
    {
        cout << "Searching in Node : " << root->value << endl;
        root = root->bstroot;
        FindKey(root, val); // next function uses bstroot to traverse through the whole bst
    }

    FindNode(root->left, val , mod);
    FindNode(root->right, val , mod);
}


//Search function for individual key
//Start traversal from bstroot till last bst node in the avl node.
void AVL_table::FindKey(Node* s, int val)
{
    if (s == NULL)
    {
        return;
    }

    if (s->bstvalue == val)
    {
        cout << "Key Found : " << s->bstvalue << endl;
    }

    FindKey(s->bstleft, val);
    FindKey(s->bstright, val);
}


//Search function uses below two functions
void AVL_table::ShowBST(Node* r, int sr)
{
    if (r == NULL)
    {
        return;
    }

    if (r->value == sr) // Finding the entered search node by user from the avl tree
    {
        cout << "Displaying BST of Node " << r->value << " : ";
        ShowBSTtraverse(r->bstroot); // sending its first bst node to Traverse function
    }

    ShowBST(r->left, sr);
    ShowBST(r->right, sr);


}

void AVL_table::ShowBSTtraverse(Node* s)
{
    if (s == NULL)
        return;

    cout << s->bstvalue << " "; // Displaying all bsts of a avl node.

    ShowBSTtraverse(s->bstleft);

    ShowBSTtraverse(s->bstright);
}

//BST creation functions
void AVL_table::MatchBST(int modval, int val, Node* r)
{
    if (r == NULL)
    {
        return;
    }

    if (r->value == modval) // uses the answer from hashkey to find the corresponding avl node
    {
        CreateBST(modval, val, r); // sends the found root , initial value , mod answer
    }
    MatchBST(modval, val, r->left);
    MatchBST(modval, val, r->right);
}

//Creating bst tree (standard iterative method)
void AVL_table::CreateBST(int modval, int val, Node* bstr)
{
    Node* newNode = new Node;
    newNode->bstleft = newNode->bstright = NULL;
    newNode->bstvalue = val;

    if (bstr->bstroot == NULL)
    {
        bstr->bstroot = newNode;
        newNode->bstleft = newNode->bstright = NULL;
        newNode->parent = bstr; // saving parent to access avl and bstroot(first bst node of a avl node)
    }
    else
    {
        newNode->parent = bstr;
        Node* tempNode = bstr->bstroot;
        while (tempNode->bstvalue != val)
        {
            if (val < tempNode->bstvalue)
            {
                if (tempNode->bstleft != NULL)
                {
                    tempNode = tempNode->bstleft;
                }
                else if (tempNode->bstleft == NULL)
                {
                    tempNode->bstleft = newNode;
                }
            }
            else if (val > tempNode->bstvalue)
            {
                if (tempNode->bstright != NULL)
                {
                    tempNode = tempNode->bstright;
                }
                else if (tempNode->bstright == NULL)
                {
                    tempNode->bstright = newNode;
                }
            }
            else
            {
                cout << "Duplicate Value" << endl;
            }
        }
    } 


    //sfml initialization for bst nodes
    newNode->bstcircle.setRadius(8);
    newNode->bstcircle.setFillColor(sf::Color::Yellow);
    newNode->bstcircle.setOutlineColor(sf::Color::Black);
    newNode->bstcircle.setOutlineThickness(0.95);
}





//SFML Printing
void AVL_table::Display(Node* r)
{

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Chaining Module with AVL and BST");
    window.setFramerateLimit(60);


    // Setting font from file
    if (!r->font.loadFromFile("res/fonts/FontFile.ttf"))
    {
        cout << "Error loading font" << endl;
    }

    r->treedata.setFont(r->font);
    r->bstdata.setFont(r->font);
    r->bstdata.setCharacterSize(10);
    r->treedata.setFillColor(sf::Color::Black);
    r->bstdata.setFillColor(sf::Color::Black);

    DrawAVLNodes(window, r, 640, 100, 10);

    cout << "Insert One BST node to start sfml window." << endl;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            else if (event.key.code == sf::Keyboard::Enter)
            {

            }


        }
        window.clear(sf::Color::White);

        printAVL(window, r); // avl for sfml
        BSTinsert(window); // Insertion for bst values
        BSTroots(root, window); // bst for sfml

        window.display();

        system("pause");
        system("cls");
        
    }
}

//Searches AVL to send first bst node to printBST function.
void AVL_table::BSTroots(Node* s , sf::RenderWindow& Window)
{
    if (s == NULL)
        return;

    BSTrootsSFML(s , Window); // sets position of first bst node in sfml
    printBST(Window , s->bstroot); // prints in runtime in sfml


    BSTroots(s->left , Window);
    BSTroots(s->right , Window);
}

//Setting bst root (first bst node position)
void AVL_table::BSTrootsSFML(Node* root , sf::RenderWindow& Window)
{
    
    if (root->bstroot != NULL)
    {
        Node* temp = root->bstroot; // temp points to bstroot

        // setting circle position and data inside circle position

        if (temp->bstleft == NULL && temp->bstright == NULL)
        {
            if (temp->parent->value == 3 || temp->parent->value == 1 || temp->parent->value == 2)
            {
                temp->bstcircle.setPosition(temp->parent->connect.getPosition());
                temp->bstcircle.move(-50, -10);
                temp->bstdata.setPosition(temp->parent->connect.getPosition());
                temp->bstdata.move(-50, -10);
            }

            else if (temp->parent->value == 0)
            {
                
                temp->bstcircle.setPosition(temp->parent->connect.getPosition());
                temp->bstcircle.move(-50, -10);
                temp->bstdata.setPosition(temp->parent->connect.getPosition());
                temp->bstdata.move(-50, -10);
            }

            else if (temp->parent->value == 7 || temp->parent->value == 8)
            {
                temp->bstcircle.setPosition(temp->parent->connect.getPosition());
                temp->bstcircle.move(+30, -8);
                temp->bstdata.setPosition(temp->bstcircle.getPosition());
            }

            else if (temp->parent->value == 4 || temp->parent->value == 6 || temp->parent->value == 9 || temp->parent->value == 5)
            {
                temp->bstcircle.setPosition(temp->parent->connect.getPosition());
                temp->bstcircle.move(-10, +38);
                temp->bstdata.setPosition(temp->bstcircle.getPosition());
            }
            

        }
    }

    int x = 575, y = 107;
    Node* temp = root->bstroot; // storing the bstroot in temp
    DrawBSTNodes(temp, x, y, Window); // sends temp(bstroot) to DrawBSTNodes to set positions of the rest of the nodes in the BST
        
}

//Setting BST Tree individually of every AVL Node
void AVL_table::DrawBSTNodes(Node*& s , int x , int y , sf::RenderWindow& Window)
{
    if (s == NULL )
    {
        return;
    }

    s->bstlink.setFillColor(sf::Color::Black);
    s->bstlink2.setFillColor(sf::Color::Black);
    s->bstlink.setSize(sf::Vector2f(40, 1));
    s->bstlink2.setSize(sf::Vector2f(40, 1));
    s->bstcircle.setFillColor(sf::Color::Yellow);


    //Setting the bst links 1 and 2 and connecting bst nodes
    if (s->parent->value == 3)
    {
        if (s->bstleft != NULL && s->bstright != NULL)
        {
            
            s->bstlink.setPosition(x, y + 8);
            s->bstlink.setRotation(150);
            s->bstlink2.setPosition(x, y + 5);
            s->bstlink2.setRotation(200);

        }
        if (s->bstleft == NULL && s->bstright != NULL)
        {
            
            s->bstlink.setPosition(x, y + 8);
            s->bstlink.setRotation(150);

        }
        if (s->bstleft != NULL && s->bstright == NULL)
        {
            
            s->bstlink.setPosition(x, y + 5);
            s->bstlink.setRotation(200);

        }
        s->bstcircle.setPosition(x, y);
    }

    if (s->parent->value == 1)
    {
        if (s->bstleft != NULL && s->bstright != NULL)
        {
            
            s->bstlink.setPosition(x - 150, y + 158);
            s->bstlink.setRotation(150);
            s->bstlink2.setPosition(x - 150, y + 158);
            s->bstlink2.setRotation(200);

        }
        if (s->bstleft == NULL && s->bstright != NULL)
        {
            
            s->bstlink.setPosition(x - 150, y + 158);
            s->bstlink.setRotation(150);

        }
        if (s->bstleft != NULL && s->bstright == NULL)
        {
           
            s->bstlink.setPosition(x - 150, y + 158);
            s->bstlink.setRotation(200);

        }
        s->bstcircle.setPosition(x-150, y+150);
    }

    if (s->parent->value == 0)
    {
        if (s->bstleft != NULL && s->bstright != NULL)
        {
           
            s->bstlink.setPosition(x - 300, y + 308);
            s->bstlink.setRotation(150);
            s->bstlink2.setPosition(x - 300, y + 308);
            s->bstlink2.setRotation(200);

        }
        if (s->bstleft == NULL && s->bstright != NULL)
        {
            
            s->bstlink.setPosition(x - 300, y + 308);
            s->bstlink.setRotation(150);

        }
        if (s->bstleft != NULL && s->bstright == NULL)
        {
            
            s->bstlink.setPosition(x - 300, y + 308);
            s->bstlink.setRotation(200);

        }
        s->bstcircle.setPosition(x - 300, y + 303);
    }

    if (s->parent->value == 4)
    {
        if (s->bstleft != NULL && s->bstright != NULL)
        {
            
            s->bstlink.setPosition(x - 75, y + 535);
            s->bstlink.setRotation(155);
            s->bstlink2.setPosition(x - 75, y + 535);
            s->bstlink2.setRotation(200);

        }
        if (s->bstleft == NULL && s->bstright != NULL)
        {
            
            s->bstlink.setPosition(x - 75, y + 535);
            s->bstlink.setRotation(155);

        }
        if (s->bstleft != NULL && s->bstright == NULL)
        {
            
            s->bstlink.setPosition(x - 75, y + 535);
            s->bstlink.setRotation(200);

        }
        s->bstcircle.setPosition(x - 75, y + 525);
    }

    if (s->parent->value == 6)
    {
        if (s->bstleft != NULL && s->bstright != NULL)
        {
            
            s->bstlink.setPosition(x + 225, y + 535);
            s->bstlink.setRotation(155);
            s->bstlink2.setPosition(x + 225, y + 535);
            s->bstlink2.setRotation(200);

        }
        if (s->bstleft == NULL && s->bstright != NULL)
        {
            
            s->bstlink.setPosition(x + 225, y + 535);
            s->bstlink.setRotation(155);

        }
        if (s->bstleft != NULL && s->bstright == NULL)
        {
           
            s->bstlink.setPosition(x + 225, y + 535);
            s->bstlink.setRotation(200);

        }
        s->bstcircle.setPosition(x + 225, y + 525);
    }

    if (s->parent->value == 9)
    {
        if (s->bstleft != NULL && s->bstright != NULL)
        {
            
            s->bstlink.setPosition(x + 528, y + 535);
            s->bstlink.setRotation(155);
            s->bstlink2.setPosition(x + 528, y + 535);
            s->bstlink2.setRotation(200);

        }
        if (s->bstleft == NULL && s->bstright != NULL)
        {
            
            s->bstlink.setPosition(x + 528, y + 535);
            s->bstlink.setRotation(155);

        }
        if (s->bstleft != NULL && s->bstright == NULL)
        {
            
            s->bstlink.setPosition(x + 528, y + 535);
            s->bstlink.setRotation(200);

        }
        s->bstcircle.setPosition(x + 528, y + 525);
    }

    if (s->parent->value == 5)
    {
        if (s->bstleft != NULL && s->bstright != NULL)
        {
            
            s->bstlink.setPosition(x + 75, y + 385);
            s->bstlink.setRotation(155);
            s->bstlink2.setPosition(x + 75, y + 385);
            s->bstlink2.setRotation(200);

        }
        if (s->bstleft == NULL && s->bstright != NULL)
        {
            
            s->bstlink.setPosition(x + 75, y + 385);
            s->bstlink.setRotation(155);

        }
        if (s->bstleft != NULL && s->bstright == NULL)
        {
            
            s->bstlink.setPosition(x + 75, y + 385);
            s->bstlink.setRotation(200);

        }
        s->bstcircle.setPosition(x + 75, y + 375);
    }

    if (s->parent->value == 2)
    {
        if (s->bstleft != NULL && s->bstright != NULL)
        {
            
            s->bstlink.setPosition(x - 45, y + 310);
            s->bstlink.setRotation(155);
            s->bstlink2.setPosition(x - 45, y + 310);
            s->bstlink2.setRotation(200);

        }
        if (s->bstleft == NULL && s->bstright != NULL)
        {
            
            s->bstlink.setPosition(x - 45, y + 310);
            s->bstlink.setRotation(155);

        }
        if (s->bstleft != NULL && s->bstright == NULL)
        {
            
            s->bstlink.setPosition(x - 45, y + 310);
            s->bstlink.setRotation(200);

        }
        s->bstcircle.setPosition(x - 45, y + 300);
    }

    if (s->parent->value == 7)
    {
        if (s->bstleft != NULL && s->bstright != NULL)
        {
            
            s->bstlink.setPosition(x + 150, y + 158);
            s->bstlink.setRotation(150);
            s->bstlink2.setPosition(x + 150, y + 158);
            s->bstlink2.setRotation(200);

        }
        if (s->bstleft == NULL && s->bstright != NULL)
        {
           
            s->bstlink.setPosition(x + 150, y + 158);
            s->bstlink.setRotation(150);

        }
        if (s->bstleft != NULL && s->bstright == NULL)
        {
           
            s->bstlink.setPosition(x + 150, y + 158);
            s->bstlink.setRotation(200);

        }
        s->bstcircle.setPosition(x + 150, y + 150);
    }

    if (s->parent->value == 8)
    {
        if (s->bstleft != NULL && s->bstright != NULL)
        {
           
            s->bstlink.setPosition(x + 300, y + 308);
            s->bstlink.setRotation(150);
            s->bstlink2.setPosition(x + 300, y + 308);
            s->bstlink2.setRotation(200);

        }
        if (s->bstleft == NULL && s->bstright != NULL)
        {
           
            s->bstlink.setPosition(x + 300, y + 308);
            s->bstlink.setRotation(150);

        }
        if (s->bstleft != NULL && s->bstright == NULL)
        {
            
            s->bstlink.setPosition(x + 300, y + 308);
            s->bstlink.setRotation(200);

        }
        s->bstcircle.setPosition(x + 300, y + 300);
    }

   
    DrawBSTNodes(s->bstleft, x-45, y - 15, Window);
    DrawBSTNodes(s->bstright, x-45, y + 15, Window);

     
}

//Printing BST using bfs (STL Queue used)
void AVL_table::printBST(sf::RenderWindow& Window, Node* s)
{
    if (s == NULL)
    {
        return;
    }

    queue<Node*> q;
    q.push(s); //storing bst root of a single avl node

    while (q.empty() == false) {
        Node* node = q.front(); // making node point to q.front() = (bstroot)

        root->bstdata.setString(to_string(node->bstvalue)); // placing bst node value into bstdata for sfml
        root->bstdata.setPosition(node->bstcircle.getPosition());
        root->bstdata.move(+3, 0); 

        Window.draw(node->bstcircle);
        Window.draw(node->bstlink);
        Window.draw(node->bstlink2);
        Window.draw(root->bstdata);
        q.pop(); // removing front

        // first left child 
        if (node->bstleft != NULL)
            q.push(node->bstleft);

        // right child
        if (node->bstright != NULL)
            q.push(node->bstright);
    }


}


// Sets sfml positions of AVL nodes , small hardcode to avoid collision between two avl nodes on sfml window.
void AVL_table::DrawAVLNodes(sf::RenderWindow& Window, Node*& node, int x, int y, int i)
{
    if (node == NULL)
    {
        return;
    }
    if (node->value == 2)
    {
        x = x - 50;
    }

    
    node->linelink.setFillColor(sf::Color::Red);
    node->linelink.setSize(sf::Vector2f(190, 2));
    node->linelink2.setFillColor(sf::Color::Red);
    node->linelink2.setSize(sf::Vector2f(190, 2));
    node->connect.setFillColor(sf::Color::Black);
    node->connect.setSize(sf::Vector2f(50, 1));
    

    if (node->right != NULL && node->left != NULL)
    {
        if (node->value == 1)
        {
            node->linelink.setPosition(x + 23, y + 30);
            node->linelink2.setPosition(x + 23, y + 30);
            node->linelink.setSize(sf::Vector2f(160, 2));
            node->linelink.rotate(55);
            node->linelink2.rotate(135);
            
        }
        else
        {
            node->linelink.setPosition(x + 23, y + 30);
            node->linelink.rotate(135);
            node->linelink2.setPosition(x + 23, y + 30);
            node->linelink2.rotate(43);
            
        }

        if (node->value == 1 || node->value == 3)
        {
            node->connect.setPosition(x, y+17);
            node->connect.rotate(180);
        }

        if (node->value == 7)
        {
            node->connect.setPosition(x, y+15);
            node->connect.rotate(180);
        }

        if (node->value == 5)
        {
            node->connect.setPosition(x + 20, y + 35);
            node->connect.rotate(90);
        }
    }
    else if (node->left == NULL && node->right != NULL)
    {
        node->linelink.setPosition(x + 15, y + 30);
        node->linelink.rotate(43);
        node->connect.setPosition(x, y);
        

        if (node->value == 8)
        {
            node->connect.setPosition(x , y + 15);
            node->connect.rotate(180);
        }
    }
    else if (node->left != NULL && node->right == NULL)
    {
        node->linelink.setPosition(x + 2, y + 25);
        node->linelink.rotate(135);
        node->connect.setPosition(x, y);
        node->connect.rotate(60);
    }
    else if (node->left == NULL && node->right == NULL)
    {
        node->connect.setPosition(x, y);

        if (node->value == 6 || node->value == 9 || node->value == 4)
        {
            node->connect.setPosition(x+20, y+35);
            node->connect.rotate(90);
        }

        if (node->value == 0)
        {
            node->connect.setPosition(x, y + 17);
            node->connect.rotate(180);
        }

        if (node->value == 2)
        {
            node->connect.setPosition(x, y+15);
            node->connect.rotate(180);
        }
    }

    //Setting AVL circle positions on window
    node->circle.setPosition(x, y);
    node->treedata.setPosition(x + 10, y - 5);

    DrawAVLNodes(Window, node->left, x - 150, y + 150, i = 10);
    DrawAVLNodes(Window, node->right, x + 150, y + 150, i = 20);

}


//Printing AVL on sfml window (Uses STL QUEUE)
void AVL_table::printAVL(sf::RenderWindow& Window, Node* root)
{
    if (root == NULL)
    {
        return;
    }

    queue<Node*> q;
    q.push(root); // storing avl node inside Queue

    while (q.empty() == false) {
        Node* node = q.front(); // node points to q.front() data

        root->treedata.setString(to_string(node->value)); // setting avl node data inside the avl node circle in sfml
        root->treedata.setPosition(node->circle.getPosition());
        root->treedata.move(+10, -5);

        //drawing nodes 1 by 1 as Queue pushes and pops
        Window.draw(node->circle);
        Window.draw(node->linelink);
        Window.draw(node->linelink2);
        Window.draw(root->treedata);
        Window.draw(node->connect);
        Window.draw(node->connect);
        q.pop();

        // Left child
        if (node->left != NULL)
            q.push(node->left);

       // Right child
        if (node->right != NULL)
            q.push(node->right);
    }


}
