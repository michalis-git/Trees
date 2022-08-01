#include <QCoreApplication>
#include <iostream>
#include <QDebug>

class Node {
public:
  int data;
  Node *left  = nullptr;
  Node *right = nullptr;

  Node(int value) {
    data = value; // value is the "value" or "key"
  }
  ~Node() {
    std::cout << "node containing " <<  data << " deleted" << std::endl;
  }

  Node *insert(Node *root, int value) {
    if (!root)
      return new Node(value);

    if (value <= root->data)
      root->left  = insert(root->left, value);
    else
      root->right = insert(root->right, value);

    return root;
  }
};

bool nodeFromKey(Node *root, int key, Node **foundNode) {
  if (!root)
    return false;

    if (nodeFromKey(root->left, key, foundNode))
        return true;
    qDebug() << root->data << "del";
    if (root->data == key) {
      qDebug() << root->data << key << root;
      *foundNode = root;
      return true;
    }
    if (nodeFromKey(root->right, key, foundNode))
        return true;
  return false;
}

bool successorFromKey(Node *root, int key, Node **succesorNode) {
  if (!root)
    return false;

  if (successorFromKey(root->left, key, succesorNode))
      return true;

  if (root->data > key) {
      *succesorNode = root;
      return true;
  }
  if (successorFromKey(root->right, key, succesorNode))
      return true;
  return false;
}

void deleteNode(Node *node, int key) {
//    Node *successor = nullptr;
//    successorFromKey(node, key, &successor);
//    node->data = successor->data;
//    node->left = successor->left;
//    node->right = successor->right;
//    successor = nullptr;
//    delete successor;
}

// left, root, right (use: non-decreasing order)
void inOrderTraverse(Node *root) {
  if (!root)
    return;

  inOrderTraverse(root->left);
  std::cout << root->data << std::endl;
  inOrderTraverse(root->right);
}

// root, left, right (use: create a copy of the tree)
void preOrderTraverse(Node *root) {
    if (!root)
      return;

    std::cout << root->data << std::endl;

    preOrderTraverse(root->left); // once the recursion started her stops, the next line is executed
    preOrderTraverse(root->right);
}

// left, right, root (delete a tree)
void postOrderTraverse(Node *root) {
  if (!root)
    return;

  postOrderTraverse(root->left);
  postOrderTraverse(root->right);
  std::cout << root->data << std::endl;
}

// delete a tree using postOrderTraversal
void deleteTree(Node *root) {
  if (!root) {
    return;
  }

  deleteTree(root->left);
  deleteTree(root->right);
  delete root;
  root = nullptr;
}


void print(const std::string& prefix, const Node* node, bool isLeft) {
    if (node != nullptr) {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->data << std::endl;

        // enter the next tree level - left and right branch
        print( prefix + (isLeft ? "│   " : "    "), node->left, true);
        print( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

void print(const Node* node) {
    print("", node, false);
}

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  Node *node = nullptr;
  Node *root = nullptr;

  root = node->insert(root, 50);
  node->insert(root, 20);
  node->insert(root, 200);
  node->insert(root, 30);
  node->insert(root, 700);
  node->insert(root, 70);
  node->insert(root, 10);

  print(root);

  inOrderTraverse(root);
  std::cout << "##########" << std::endl;

  Node *foundNode = nullptr;
  nodeFromKey(root, 20, &foundNode);
  std::cout <<  "foundNode: " <<  foundNode->data << std::endl;
  Node *successorNode = nullptr;
  successorFromKey(root, 20, &successorNode);
  std::cout << "successor: " << successorNode->data << std::endl;

  deleteNode(root, 20);
  print(root);

  // free memory
  deleteTree(root);

  return a.exec();
}
