#include <iostream>
using namespace std;

const int MAX = 100;
const int INF = 1e9;

void dijikstra(int graph[MAX][MAX], int V, int source, string location[]){
    int dist[MAX];
    bool visited[MAX];

    for (int i =0;i<V;i++){
        dist[i] = INF;
        visited[i] = false;
    }

    dist[source] = 0;

    for(int count = 0 ; count < V-1;count ++){
        int mindist = INF,u;

        for(int v=0;v<V;v++){
            if(!visited[v] && dist[v] < mindist){
                mindist = dist[v];
                u=v;
            }
        }
        visited[u] = true;

        for(int v = 0;v<V;v++){
            if(graph[u][v] && !visited[v] && dist[u] + graph[u][v] < dist[v]){
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    cout <<"shortest distance is : " << endl;
    for (int i=0;i<V;i++){
        cout << location[i] << ":" << dist[i] << endl;
    }
}

int main (){
    int V = 5;
    string locations[] = {
        "Supplier",
        "Warehouse",
        "Distribution Center",
        "Retail Store A",
        "Retail Store B"
    };
    int graph[MAX][MAX] = {
        // S  W  D  A  B
        {0, 4, 0, 0, 10}, // Supplier
        {4, 0, 3, 0, 0},  // Warehouse
        {0, 3, 0, 2, 4},  // Distribution Center
        {0, 0, 2, 0, 1},  // Retail Store A
        {10, 0, 4, 1, 0}  // Retail Store B
    };

    int source = 1;
    dijikstra(graph,V,source,locations);

    return 0;

}
