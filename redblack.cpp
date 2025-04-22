#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Directory {
    string name;
    Color color;
    Directory *left, *right, *parent;

    Directory(string name) {
        this->name = name;
        color = RED; // New nodes are always RED
        left = right = parent = NULL;
    }
};

class FileSystem {
private:
    Directory* root;

    // Left Rotate
    void leftRotate(Directory*& root, Directory* x) {
        Directory* y = x->right;
        x->right = y->left;
        if (y->left != NULL)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == NULL)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    // Right Rotate
    void rightRotate(Directory*& root, Directory* y) {
        Directory* x = y->left;
        y->left = x->right;
        if (x->right != NULL)
            x->right->parent = y;

        x->parent = y->parent;

        if (y->parent == NULL)
            root = x;
        else if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;

        x->right = y;
        y->parent = x;
    }

    // Fix Red-Black Tree rules after insertion
    void fixInsert(Directory*& root, Directory* z) {
        while (z != root && z->parent->color == RED) {
            Directory* grandparent = z->parent->parent;

            if (z->parent == grandparent->left) {
                Directory* uncle = grandparent->right;

                if (uncle && uncle->color == RED) {
                    // Case 1: Uncle is RED -> recolor
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    z = grandparent;
                } else {
                    if (z == z->parent->right) {
                        // Case 2: Left-Right
                        z = z->parent;
                        leftRotate(root, z);
                    }
                    // Case 3: Left-Left
                    z->parent->color = BLACK;
                    grandparent->color = RED;
                    rightRotate(root, grandparent);
                }
            } else {
                Directory* uncle = grandparent->left;

                if (uncle && uncle->color == RED) {
                    // Case 1: Uncle is RED -> recolor
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    z = grandparent;
                } else {
                    if (z == z->parent->left) {
                        // Case 2: Right-Left
                        z = z->parent;
                        rightRotate(root, z);
                    }
                    // Case 3: Right-Right
                    z->parent->color = BLACK;
                    grandparent->color = RED;
                    leftRotate(root, grandparent);
                }
            }
        }
        root->color = BLACK; // root is always BLACK
    }

    Directory* insertHelper(Directory* root, Directory* node) {
        if (root == NULL)
            return node;

        if (node->name < root->name) {
            root->left = insertHelper(root->left, node);
            root->left->parent = root;
        } else if (node->name > root->name) {
            root->right = insertHelper(root->right, node);
            root->right->parent = root;
        }
        return root;
    }

    void inorder(Directory* root){
        if(root != NULL) {
            inorder(root->left);
        cout << root-> name << "(";
        if(root->color == RED){
            cout <<"RED";
        }else{
            cout <<"BLACK";
        }
        cout << ")" << endl;
        inorder(root->right);
        }
    }

public:
    FileSystem() {
        root = NULL;
    }

    void insert(string name) {
        Directory* newNode = new Directory(name);
        root = insertHelper(root, newNode);
        fixInsert(root, newNode);
    }

    void show() {
        cout << "\nDirectory Structure:\n";
        inorder(root);
    }
};

int main() {
    FileSystem fs;

    fs.insert("home");
    fs.insert("documents");
    fs.insert("downloads");
    fs.insert("pictures");
    fs.insert("videos");
    fs.insert("music");
    fs.insert("games");

    fs.show();

    return 0;
}
