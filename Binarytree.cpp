#include <iostream>
using namespace std;

struct Node {
    int value;
    Node *left;
    Node *right;
};

Node *createNode(int value) {
    Node *newNode = new Node;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

bool search(Node *root, int value) {
    if (root == NULL) {
        return false;
    }
    if (root->value == value) {
        return true;
    }
    if (value < root->value) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}

void insert(Node *&root, int value) {
    if (root == NULL) {
        root = createNode(value);
        return;
    }
    if(search(root, value)){
        cout << "Valor já existe na árvore" << endl;
        return;
    }

    if (value < root->value) {
        insert(root->left, value);
    } else {
        insert(root->right, value);
    }
}


void printTree(Node *root, int level = 0) {
    if (root == NULL) return;

    for (int i = 0; i < level; i++) {
        cout << "-";
    }
    cout << root->value << endl;

    printTree(root->left, level + 1);
    printTree(root->right, level + 1);
}

int countNodes(Node *root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countLeaves(Node *root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

int main() {
    Node *root = NULL;
    int n, value;

    cout << "Digite o número de nós: ";
    cin >> n;

    cout << "Digite os valores dos nós:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> value;
        insert(root, value);
    }

    cout << "Árvore binária:" << endl;
    printTree(root);

    cout << "Número total de nós: " << countNodes(root) << endl;
    cout << "Número total de folhas: " << countLeaves(root) << endl;

    return 0;
}
