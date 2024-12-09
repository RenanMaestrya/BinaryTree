#include <iostream>
#include <queue>
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

    if (search(root, value)) {
        cout << "Valor já existe na árvore. Insira outro valor: ";
        int newValue;
        cin >> newValue;
        insert(root, newValue);
        return;
    }

    if (value < root->value) {
        insert(root->left, value);
    } else {
        insert(root->right, value);
    }
}


Node* findMin(Node *root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node* removeNode(Node *root, int value) {
    if (root == NULL) {
        return NULL;
    }
    if (value < root->value) {
        root->left = removeNode(root->left, value);
    } else if (value > root->value) {
        root->right = removeNode(root->right, value);
    } else {
        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        } else if (root->left == NULL) {
            Node *temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            delete root;
            return temp;
        } else {
            Node *temp = findMin(root->right);
            root->value = temp->value;
            root->right = removeNode(root->right, temp->value);
        }
    }
    return root;
}

void LevelRoute(Node *root) {
    if (root == NULL) {
        cout << "Árvore vazia." << endl;
        return;
    }

    queue<Node *> q;
    q.push(root);

    while (!q.empty()) {
        Node *current = q.front();
        q.pop();

        cout << current->value << " ";

        if (current->left != NULL) q.push(current->left);
        if (current->right != NULL) q.push(current->right);
    }
    cout << endl;
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

void insertMultiple(Node *&root) {
    int n, value;
    cout << "Quantos números deseja inserir? ";
    cin >> n;

    cout << "Digite os valores a serem inseridos: ";
    int i = 0;
    while(i < n) {
        cin >> value;
        if(search(root, value)) {
            cout << "Valor já existe na árvore. Insira outro valor: ";
            continue;
        }else {
            insert(root, value);
        }
        i++;
    }
    cout << "Valores processados!" << endl;
}

void printMenu() {
    cout << "\n===== Menu =====" << endl;
    cout << "1. Inserir valor único" << endl;
    cout << "2. Inserir múltiplos valores" << endl;
    cout << "3. Remover valor" << endl;
    cout << "4. Imprimir percurso em nível" << endl;
    cout << "5. Imprimir árvore" << endl;
    cout << "6. Sair" << endl;
    cout << "Escolha uma opção: ";
}

int main() {
    Node *root = NULL;
    int choice, value;

    while (true) {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Digite o valor para inserir: ";
                cin >> value;
                insert(root, value);
                break;
            case 2:
                insertMultiple(root);
                break;
            case 3:
                cout << "Digite o valor para remover: ";
                cin >> value;
                if (search(root, value)) {
                    root = removeNode(root, value);
                    cout << "Valor removido!" << endl;
                } else {
                    cout << "Valor não encontrado na árvore." << endl;
                }
                break;
            case 4:
                LevelRoute(root);
                break;
            case 5:
                cout << "Árvore:" << endl;
                printTree(root);
                break;
            case 6:
                cout << "Saindo do programa..." << endl;
                return 0;
            default:
                cout << "Opção inválida! Tente novamente." << endl;
        }
    }

    return 0;
}
