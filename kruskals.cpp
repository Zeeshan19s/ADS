#include <iostream>
using namespace std;

// Class to store each edge
class Edge {
public:
    int src, dest, weight;
    Edge() {} // Default constructor
    Edge(int s, int d, int w) {
        src = s;
        dest = d;
        weight = w;
    }
};

// Function to find the parent of a vertex (Disjoint Set)
int findParent(int parent[], int v) {
    if (parent[v] == v)
        return v;
    return findParent(parent, parent[v]);
}

// Function to join two sets (Union)
void unionSets(int parent[], int u, int v) {
    int pu = findParent(parent, u);
    int pv = findParent(parent, v);
    parent[pu] = pv;
}

// Kruskal's Algorithm to find MST
void kruskalMST(Edge edges[], int V, int E) {
    int parent[10];         // Store parent of each vertex
    Edge mst[10];           // To store MST result
    int count = 0;          // Number of edges in MST

    // Initialize each vertex as its own parent
    for (int i = 0; i < V; i++)
        parent[i] = i;

    // Sort edges by weight (Bubble Sort)
    for (int i = 0; i < E - 1; i++) {
        for (int j = 0; j < E - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    // Pick edges one by one
    for (int i = 0; i < E && count < V - 1; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;

        // If u and v are in different sets, include this edge
        if (findParent(parent, u) != findParent(parent, v)) {
            mst[count] = edges[i];
            count++;
            unionSets(parent, u, v);
        }
    }

    // Print result
    cout << "\nMinimum Spanning Tree:\n";
    for (int i = 0; i < count; i++) {
        cout << mst[i].src << " - " << mst[i].dest << " : " << mst[i].weight << endl;
    }
}

// Main function
int main() {
    int V = 4; // Number of vertices
    int E = 5; // Number of edges

    // Declare and define edges
    Edge edges[] = {
        Edge(0, 1, 10),
        Edge(0, 2, 6),
        Edge(0, 3, 5),
        Edge(1, 3, 15),
        Edge(2, 3, 4)
    };

    kruskalMST(edges, V, E);

    return 0;
}

