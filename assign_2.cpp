#include <iostream>
using namespace std;

class Player {
public:
    int player_id;
    int score;
    Player* left;
    Player* right;
    int height;

    Player(int id, int sc) {
        player_id = id;
        score = sc;
        left = right = nullptr;
        height = 1;
    }
};

// Utility to get height of tree
int height(Player* node) {
    return node ? node->height : 0;
}

// Utility to get balance factor
int getBalance(Player* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Right rotate
Player* rightRotate(Player* y) {
    Player* x = y->left;
    Player* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

// Left rotate
Player* leftRotate(Player* x) {
    Player* y = x->right;
    Player* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

// Insert a player
Player* insert(Player* root, int id, int score) {
    if (root == nullptr)
        return new Player(id, score);

    if (score > root->score) // higher scores go left (for descending leaderboard)
        root->left = insert(root->left, id, score);
    else if (score < root->score)
        root->right = insert(root->right, id, score);
    else
        return root; // Duplicate score, skip

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // Balance AVL tree
    if (balance > 1 && score > root->left->score)
        return rightRotate(root);
    if (balance < -1 && score < root->right->score)
        return leftRotate(root);
    if (balance > 1 && score < root->left->score) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && score > root->right->score) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Find the node with minimum score
Player* minValueNode(Player* node) {
    Player* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Delete a player by ID
Player* deletePlayer(Player* root, int score) {
    if (root == nullptr)
        return root;

    // Traverse to find player by ID
    if (score < root->player_id)
        root->left = deletePlayer(root->left, score);
    else if (score > root->player_id)
        root->right = deletePlayer(root->right, score);
    else {
        // Found the player
        if (root->left == nullptr || root->right == nullptr) {
            Player* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }
        Player* temp = minValueNode(root->right);
        root->player_id = temp->player_id;
        root->score = temp->score;
        root->right = deletePlayer(root->right, temp->player_id);
    }

    // Update height and balance
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // Balance the tree
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Display leaderboard (in descending order)
void displayLeaderboard(Player* root) {
    if (root != nullptr) {
        displayLeaderboard(root->left);
        cout << "Player ID: " << root->player_id << ", S    core: " << root->score << endl;
        displayLeaderboard(root->right) ;
    }
}

// Main function
int main() {
    Player* root = nullptr;
    int choice;

    while (true) {
        cout << "\n--- Multiplayer Game System ---\n";
        cout << "1. Register Player\n";
        cout << "2. Display Leaderboard\n";
        cout << "3. Remove Player\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id, score;
            cout << "Enter Player ID: ";
            cin >> id;
            cout << "Enter Score: ";
            cin >> score;
            root = insert(root, id, score);
        } else if (choice == 2) {
            cout << "\n--- Leaderboard ---\n";
            displayLeaderboard(root);
        } else if (choice == 3) {
            int id;
            cout << "Enter Player ID to remove: ";
            cin >> id;
            root = deletePlayer(root, id);
        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }


    return 0;
}
