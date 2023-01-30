// This is a template header file. You can use the template to create your own
// bintree.h you add class/method comments and assumptions

#include "nodedata.h" // node data
#include <iostream>   //input and output

using namespace std;

class BinTree {

  friend ostream &operator<<(ostream &, const BinTree &);

public:
  BinTree();                         // constructor
  BinTree(const BinTree &otherTree); // copy constructor
  ~BinTree();                        // destructor, calls makeEmpty
  bool isEmpty() const;              // true if tree is empty, otherwise false
  void makeEmpty(); // make the tree empty so isEmpty returns true
  BinTree &operator=(const BinTree &);
  bool operator==(const BinTree &) const;
  bool operator!=(const BinTree &) const;
  bool insert(NodeData *);
  bool retrieve(const NodeData &, NodeData *&);
  void displaySideways() const; // provided below, displays the tree sideways
  int getHeight(const NodeData &) const;
  void bstreeToArray(NodeData *[]);
  void arrayToBSTree(NodeData *[]);

private:
  struct Node {
    NodeData *data; // pointer to data object
    Node *left;     // left subtree pointer
    Node *right;    // right subtree pointer
    ~Node() {
      if (data) {
        delete data;
      }
    }
  };
  Node *root; // root of the tree

  // utility functions: The followings are just examples of your private method
  void inorderHelper(ostream &out, Node *curr) const;
  void sideways(Node *, int) const;
  void makeEmptyRecursive(Node *&curr); // recursive function for makeEmpty
  bool insertRecursive(Node *&curr,
                       NodeData *data); // recursive function for insert
  void copyRecursive(Node *otherTree,
                     Node *&tree); // recursive function for = operator
  bool equalRecursive(Node *node1,
                      Node *node2) const; // recursive function for == operator
  bool retrieveRecursive(Node *&, const NodeData &,
                         NodeData *&) const; // recursive function for retrieve
  int getHeightRecursive(const NodeData &, Node *) const;
  int heightRecursiveHelp(Node *) const;
  void arrayInOrder(Node *, NodeData *[], int &);
  void arrayBstRecursive(Node *, NodeData *[], int, int);
};

/* The followings are the example of how to implement displaySideways.
You should put the implementation to bintree.cpp, and you can modify this for
your convenience.
*/

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
// void BinTree::displaySideways() const { sideways(root, 0); }

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
// void BinTree::sideways(Node *current, int level) const {
//   if (current != NULL) {
//     level++;
//     sideways(current->right, level);

//     // indent for readability, 4 spaces per depth level
//     for (int i = level; i >= 0; i--) {
//       cout << "    ";
//     }

//     cout << *current->data << endl; // display information of object
//     sideways(current->left, level);
//   }
// }