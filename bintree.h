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
  void makeEmptyRecursive(Node *&); // recursive function for makeEmpty
  bool insertRecursive(Node *&,
                       NodeData *); // recursive function for insert
  void copyRecursive(Node *,
                     Node *&); // recursive function for = operator
  bool equalRecursive(Node *,
                      Node *) const; // recursive function for == operator
  bool retrieveRecursive(Node *&, const NodeData &,
                         NodeData *&) const; // recursive function for retrieve
  int getHeightRecursive(const NodeData &, Node *)
      const; // recursive function for finding the data
  int heightRecursiveHelp(
      Node *) const; // another recursive function to get the height
  void arrayInOrder(Node *, NodeData *[],
                    int &); // recursive function for bstreeToArray
  void arrayBstRecursive(Node *, NodeData *[], int,
                         int); // recursive function for arraytobstree
};