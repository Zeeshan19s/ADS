#include <iostream>
using namespace std;

const int MAX = 100;
const int INF = 1e9; // Represents infinity

void primMST(int adj[MAX][MAX], int V) {
    int parent[MAX];   // Stores the MST
    int key[MAX];      // Minimum weight edge to a vertex
    bool mstSet[MAX];  // True if vertex is included in MST

    // Initialize all keys as infinite and mstSet[] as false
    for (int i = 0; i < V; i++) {
        key[i] = INF;
        mstSet[i] = false;
    }

    // Start from the first vertex
    key[0] = 0;
    parent[0] = -1; // First node is the root of MST

    // Construct MST with V vertices
    for (int count = 0; count < V - 1; count++) {
        // Find the vertex with the minimum key value not yet included in MST
        int minKey = INF, u;

        for (int v = 0; v < V; v++) {
            if (!mstSet[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        // Add the selected vertex to the MST
        mstSet[u] = true;

        // Update key and parent for adjacent vertices
        for (int v = 0; v < V; v++) {
            if (adj[u][v] && !mstSet[v] && adj[u][v] < key[v]) {
                parent[v] = u;
                key[v] = adj[u][v];
            }
        }
    }

    // Display the constructed MST
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++)
        cout << parent[i] << " - " << i << "\t" << adj[i][parent[i]] << "\n";
}

int main() {
    int V = 5;
    int adj[MAX][MAX] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    primMST(adj, V);
    return 0;
}
