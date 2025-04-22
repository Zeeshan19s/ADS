#include <iostream>
#include <stack>
using namespace std;

const int MAX = 100;

void DFS(int adj[MAX][MAX], int V, int source){
    int result[MAX];
    bool visited[MAX];
    int count = 0;

    for(int i=0;i<V;i++){
        visited[i] = false;
    }

    stack <int> s;
    s.push(source);
    visited[source] = true;

    while(!s.empty()){
        int curr = s.top();
        s.pop();
        result[count++] = curr;

        for(int i =0;i<V;i++){
            if(adj[curr][i] == 1 && !visited[i]){
                s.push(i);
                visited[i] = true;
            }
        }
    }

    for (int i=0;i<count;i++){
        cout << result[i] << " " ;
    }
    cout << endl;
}
int main (){
    int V = 5;
    int adj[MAX][MAX] = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 0, 0, 1},
        {0, 0, 1, 1, 0}
    };
    int source = 0;
    DFS(adj,V,source);
    return 0;
}