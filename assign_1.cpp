#include <iostream>
#include <queue>
using namespace std;

class Node {
public:
    string key;
    string value;
    Node* left;
    Node* right;

    Node(string k, string v) {
        key = k;
        value = v;
        left = right = NULL;
    }
};

class DictionaryBST {
private:
    Node* root;

    Node* insert(Node* node, string key, string value) {
        if (node == NULL) {
            return new Node(key, value);
        }
        if (key == node->key) {
            cout << "Duplicate word found. Updating value.\n";
            node->value = value;
        } else if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else {
            node->right = insert(node->right, key, value);
        }
        return node;
    }

    Node* search(Node* node, string key) {
        if (node == NULL || node->key == key) {
            return node;
        }
        if (key < node->key) {
            return search(node->left, key);
        } else {
            return search(node->right, key);
        }
    }

    Node* getSuccessor(Node* curr) {
        curr = curr->right;
        while (curr != NULL && curr->left != NULL) {
            curr = curr->left;
        }
        return curr;
    }

    Node* deleteNode(Node* node, string key) {
        if (node == NULL) return NULL;

        if (key < node->key) {
            node->left = deleteNode(node->left, key);
        } else if (key > node->key) {
            node->right = deleteNode(node->right, key);
        } else {
            if (node->left == NULL) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (node->right == NULL) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* succ = getSuccessor(node);
            node->key = succ->key;
            node->value = succ->value;
            node->right = deleteNode(node->right, succ->key);
        }
        return node;
    }

    void inorder(Node* node) {
        if (node != NULL) {
            inorder(node->left);
            cout << node->key << " : " << node->value << endl;
            inorder(node->right);
        }
    }

    Node* mirror(Node* node) {
        if (node == NULL) return NULL;
        Node* newNode = new Node(node->key, node->value);
        newNode->left = mirror(node->right);
        newNode->right = mirror(node->left);
        return newNode;
    }

    Node* copyTree(Node* node) {
        if (node == NULL) return NULL;
        Node* newNode = new Node(node->key, node->value);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }

    void levelOrder(Node* root) {
        if (root == NULL) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* temp = q.front(); q.pop();
            cout << temp->key << " : " << temp->value << endl;
            if (temp->left != NULL) q.push(temp->left);
            if (temp->right != NULL) q.push(temp->right);
        }
    }

public:
    DictionaryBST() {
        root = NULL;
    }

    void insert(string key, string value) {
        root = insert(root, key, value);
    }

    void deleteWord(string key) {
        root = deleteNode(root, key);
    }

    void search(string key) {
        Node* result = search(root, key);
        if (result != NULL) {
            cout << "Found: " << result->key << " : " << result->value << endl;
        } else {
            cout << "Word not found." << endl;
        }
    }

    void display() {
        cout << "Dictionary (Inorder Traversal):\n";
        inorder(root);
    }

    void displayLevelWise() {
        cout << "Dictionary (Level Order Traversal):\n";
        levelOrder(root);
    }

    void mirrorImage() {
        Node* mirrorRoot = mirror(root);
        cout << "Mirror Image of Dictionary:\n";
        inorder(mirrorRoot);
    }

    void copyDictionary() {
        Node* copiedRoot = copyTree(root);
        cout << "Copied Dictionary:\n";
        inorder(copiedRoot);
    }
};

int main() {
    DictionaryBST dict;

    dict.insert("apple", "A fruit");
    dict.insert("ball", "A toy");
    dict.insert("cat", "An animal");
    dict.insert("dog", "A loyal animal");
    dict.insert("elephant", "A big animal");

    dict.display();

    dict.search("cat");
    dict.search("fish");

    dict.deleteWord("dog");
    cout << "\nAfter deleting 'dog':\n";
    dict.display();

    dict.displayLevelWise();

    dict.mirrorImage();

    dict.copyDictionary();

    return 0;
}
