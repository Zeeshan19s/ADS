#include <iostream>
#include <queue>
using namespace std;

const int ORDER = 3;

struct BTreeNode {
    int keys[2]; // Max 2 keys for order 3
    BTreeNode* children[3]; // Max 3 children
    int numKeys;
    bool isLeaf;

    BTreeNode() {
        numKeys = 0;
        isLeaf = true;
        for (int i = 0; i < 3; i++) children[i] = NULL;
    }
};

class BTree {
    BTreeNode* root;

public:
    BTree() {
        root = new BTreeNode();
    }

    void insert(int key);
    void levelOrderDisplay();

private:
    void insertNonFull(BTreeNode* node, int key);
    void splitChild(BTreeNode* parent, int i);
};

void BTree::insert(int key) {
    if (root->numKeys == 2) {
        BTreeNode* newRoot = new BTreeNode();
        newRoot->isLeaf = false;
        newRoot->children[0] = root;
        splitChild(newRoot, 0);
        root = newRoot;
    }
    insertNonFull(root, key);
}

void BTree::splitChild(BTreeNode* parent, int i) {
    BTreeNode* full = parent->children[i];
    BTreeNode* newNode = new BTreeNode();
    newNode->isLeaf = full->isLeaf;
    newNode->keys[0] = full->keys[1];
    newNode->numKeys = 1;
    full->numKeys = 1;

    if (!full->isLeaf)
        newNode->children[0] = full->children[2];

    for (int j = parent->numKeys; j > i; j--) {
        parent->children[j + 1] = parent->children[j];
        parent->keys[j] = parent->keys[j - 1];
    }

    parent->children[i + 1] = newNode;
    parent->keys[i] = full->keys[1];
    parent->numKeys++;
}

void BTree::insertNonFull(BTreeNode* node, int key) {
    int i = node->numKeys - 1;

    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        while (i >= 0 && key < node->keys[i]) i--;
        i++;
        if (node->children[i]->numKeys == 2) {
            splitChild(node, i);
            if (key > node->keys[i]) i++;
        }
        insertNonFull(node->children[i], key);
    }
}

void BTree::levelOrderDisplay() {
    queue<BTreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            BTreeNode* node = q.front(); q.pop();
            for (int i = 0; i < node->numKeys; i++)
                cout << node->keys[i] << " ";
            cout << "| ";
            if (!node->isLeaf)
                for (int i = 0; i <= node->numKeys; i++)
                    q.push(node->children[i]);
        }
        cout << endl;
    }
}

int main() {
    BTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(12);

    cout << "Level Order Display:\n";
    tree.levelOrderDisplay();

    return 0;
} 