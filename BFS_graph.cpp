#include <iostream>
#include <queue>

using namespace std;

const int MAX = 100;

void BFS(int adj[MAX][MAX],int V,int source){
    bool visited[MAX] = {false};
    int result[MAX];
    int index = 0;
    
    // initialise queue;
    queue <int> q;

    //start from the source 
    visited [source] = true;
    q.push(source);

    while(!q.empty()){
        int curr = q.front();
        q.pop();
        result[index++] = curr;

        // check for all the neighboors
        for (int i=0;i<V;i++){
            if(adj[curr][i] == 1 && !visited[i]){
                visited[i] = true;
                q.push(i);
                
            }
        }
    }

    //print BFS array
    cout <<"printing the BFS" << endl;
    for(int i =0;i<index;i++){
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
    BFS(adj,V,source);
    return 0;

}