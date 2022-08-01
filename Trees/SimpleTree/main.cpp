#include <QCoreApplication>
#include <iostream>

class Node {
public:
  int data;
  Node *left  = nullptr;
  Node *right = nullptr;

  Node(int value) {
    data = value; // value is the "value" or "key"
  }
};

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

  Node *root  = new Node(1);
  root->left  = new Node(2);
  root->right = new Node(3);
  root->left->left = new Node(4);

  print(root);

  /* 4 becomes left child of 2
                1
              /    \
             2      3
            / \     / \
           4 NULL NULL NULL
          / \
        NULL NULL
  */

  return a.exec();
}
