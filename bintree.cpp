#include "bintree.h"

using namespace std;

ostream &operator<<(ostream &out, const BinTree &binTree) {
  if (binTree.root == NULL) {
    return out;
  }
  binTree.inorderHelper(out, binTree.root);
  out << endl;
  return out;
}

void BinTree::inorderHelper(ostream &out, Node *curr) const {
  if (curr == NULL) {
    return;
  } else {
    inorderHelper(out, curr->left);
    out << *curr->data << " ";
    inorderHelper(out, curr->right);
  }
}

BinTree::BinTree() { this->root = NULL; }

BinTree::BinTree(const BinTree &otherTree) {
  this->root = NULL;
  *this = otherTree;
}

BinTree &BinTree::operator=(const BinTree &otherTree) {
  if (this->isEmpty() || otherTree.isEmpty()) {
    this->makeEmpty();
    return *this;
  }
  if (*this == otherTree) {
    return *this;
  }
  this->makeEmpty();
  copyRecursive(otherTree.root, this->root);
  return *this;
}

void BinTree::copyRecursive(Node *otherTree, Node *&tree) {
  if (otherTree == NULL) {
    tree = NULL;
  } else {
    tree = new Node;
    NodeData *temp = new NodeData(*otherTree->data);
    tree->data = temp;
    copyRecursive(otherTree->left, tree->left);
    copyRecursive(otherTree->right, tree->right);
    delete temp;
    delete tree;
  }
}

BinTree::~BinTree() {
  this->root = NULL;
  makeEmpty();
}

bool BinTree::isEmpty() const { return this->root == NULL; }

void BinTree::makeEmpty() {
  makeEmptyRecursive(this->root);
  this->root = NULL;
}

void BinTree::makeEmptyRecursive(Node *&curr) {
  if (curr == NULL) {
    return;
  } else {
    makeEmptyRecursive(curr->left);
    makeEmptyRecursive(curr->right);
  }
  if (curr->data != NULL) {
    delete curr->data;
    curr->data = NULL;
  }
  delete curr;
  curr = NULL;
}

bool BinTree::insert(NodeData *data) {
  return insertRecursive(this->root, data);
}

bool BinTree::insertRecursive(Node *&curr, NodeData *data) {
  if (curr == NULL) {
    curr = new Node;
    curr->data = data;
    curr->right = NULL;
    curr->left = NULL;
  } else if (*data < *curr->data) {
    insertRecursive(curr->left, data);
  } else if (*data > *curr->data) {
    insertRecursive(curr->right, data);
  } else if (*data == *curr->data) {
    return false;
  } else {
    return false;
  }
  return true;
}

bool BinTree::retrieve(const NodeData &takeData, NodeData *&theData) {
  retrieveRecursive(this->root, takeData, theData);
  return theData != NULL;
}

bool BinTree::retrieveRecursive(Node *&curr, const NodeData &takeData,
                                NodeData *&theData) const {
  if (curr == NULL) {
    theData = NULL;
    return false;
  }
  if (*curr->data == takeData) {
    theData = curr->data;
    return true;
  } else if (takeData > *curr->data) {
    retrieveRecursive(curr->right, takeData, theData);
  } else if (takeData < *curr->data) {
    retrieveRecursive(curr->left, takeData, theData);
  } else {
    return false;
  }
  return true;
}

int BinTree::getHeight(const NodeData &data) const {
  return getHeightRecursive(data, this->root);
}

int BinTree::getHeightRecursive(const NodeData &data, Node *curr) const {
  if (curr == NULL) {
    return 0;
  } else if (*curr->data == data) {
    return heightRecursiveHelp(curr);
  }
  int heightRight = getHeightRecursive(data, curr->right);
  int heightLeft = getHeightRecursive(data, curr->left);
  return max(heightRight, heightLeft);
}

int BinTree::heightRecursiveHelp(Node *curr) const {
  if (curr == nullptr) {
    return 0;
  }
  return 1 +
         max(heightRecursiveHelp(curr->left), heightRecursiveHelp(curr->right));
}

void BinTree::displaySideways() const { sideways(root, 0); }

void BinTree::sideways(Node *current, int level) const {
  if (current != NULL) {
    level++;
    sideways(current->right, level);
    for (int i = level; i >= 0; i--) {
      cout << "    ";
    }
    cout << *current->data << endl;
    sideways(current->left, level);
  }
}

bool BinTree::operator==(const BinTree &otherTree) const {
  if ((this->isEmpty() && !otherTree.isEmpty()) ||
      (!this->isEmpty() && otherTree.isEmpty())) {
    return false;
  }
  if (root == NULL && otherTree.root == NULL) {
    return true;
  } else {
    return *root->data == *otherTree.root->data &&
           equalRecursive(root, otherTree.root);
  }
}

bool BinTree::equalRecursive(Node *node1, Node *node2) const {
  if (node1 == NULL && node2 == NULL) {
    return true;
  } else if (node1 == NULL || node2 == NULL) {
    return false;
  }
  if (node1->left == NULL && node2->left == NULL && node1->right == NULL &&
      node2->right == NULL && *node1->data == *node2->data) {
    return true;
  }
  return equalRecursive(node1->left, node2->left) &&
         equalRecursive(node1->right, node2->right);
}

bool BinTree::operator!=(const BinTree &otherTree) const {
  return !(*this == otherTree);
}

void BinTree::bstreeToArray(NodeData *arr[]) {
  int index = 0;
  arrayInOrder(root, arr, index);
  makeEmpty();
}

void BinTree::arrayInOrder(Node *curr, NodeData *arr[], int &index) {
  if (curr == nullptr) {
    return;
  } else {
    arrayInOrder(curr->left, arr, index);
    NodeData *temp;
    temp = curr->data;
    curr->data = NULL;
    arr[index++] = temp;
    *(arr + index) = temp;
    arrayInOrder(curr->right, arr, index);
  }
}

void BinTree::arrayToBSTree(NodeData *arr[]) {
  makeEmpty();  // make tree empty to make sure that the tree is empty
  int high = 0; // high is the highest
  while (arr[high] != NULL) {
    high++;
  }
  arrayBstRecursive(root, arr, 0, high - 1);
  for (int i = 0; i < high; i++) {
    arr[i] = NULL;
  }
}

void BinTree::arrayBstRecursive(Node *curr, NodeData *arr[], int low,
                                int high) {
  if (low > high) {
    curr = NULL;
  } else {
    int mid = (low + high) / 2;
    NodeData *temp;
    temp = arr[mid];
    insert(temp);
    arrayBstRecursive(curr, arr, low, mid - 1);
    arrayBstRecursive(curr, arr, mid + 1, high);
  }
}