#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

const int MAX = 100;
int maze[MAX][MAX];
bool visited[MAX][MAX];
pair<int, int> parent[MAX][MAX];

int rows = 5, cols = 5;

// Directions: up, down, left, right
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool isValid(int x, int y) {
    return (x >= 0 && y >= 0 && x < rows && y < cols &&
            maze[x][y] == 0 && !visited[x][y]);
}

void printPath(pair<int, int> goal) {
    pair<int, int> path[1000];
    int count = 0;
    int x = goal.first, y = goal.second;

    while (!(x == -1 && y == -1)) {
        path[count++] = {x, y};
        pair<int, int> p = parent[x][y];
        x = p.first;
        y = p.second;
    }

    // Print in reverse
    for (int i = count - 1; i >= 0; i--) {
        cout << "(" << path[i].first << "," << path[i].second << ") ";
    }
    cout << endl;
}

// BFS with path printing
void BFS(int sx, int sy, int gx, int gy) {
    queue<pair<int, int>> q;

    // Reset visited and parent
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            visited[i][j] = false;
            parent[i][j] = {-1, -1};
        }

    q.push({sx, sy});
    visited[sx][sy] = true;

    bool found = false;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if (x == gx && y == gy) {
            found = true;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isValid(nx, ny)) {
                visited[nx][ny] = true;
                parent[nx][ny] = {x, y};
                q.push({nx, ny});
            }
        }
    }

    if (found) {
        cout << "BFS Path Found: ";
        printPath({gx, gy});
    } else {
        cout << "No path found using BFS.\n";
    }
}

// DFS helper function
bool DFSUtil(int x, int y, int gx, int gy) {
    visited[x][y] = true;

    if (x == gx && y == gy)
        return true;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (isValid(nx, ny)) {
            parent[nx][ny] = {x, y};
            if (DFSUtil(nx, ny, gx, gy))
                return true;
        }
    }

    return false;
}

// DFS with path printing
void DFS(int sx, int sy, int gx, int gy) {
    // Reset visited and parent
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            visited[i][j] = false;
            parent[i][j] = {-1, -1};
        }

    bool found = DFSUtil(sx, sy, gx, gy);

    if (found) {
        cout << "DFS Path Found: ";
        printPath({gx, gy});
    } else {
        cout << "No path found using DFS.\n";
    }
}

int main() {
    // Define simple maze
    int exampleMaze[5][5] = {
        {0, 0, 1, 0, 0},
        {1, 0, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0}
    };

    // Copy maze
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            maze[i][j] = exampleMaze[i][j];

    int startX = 0, startY = 0;
    int goalX = 4, goalY = 4;

    cout << "Running BFS...\n";
    BFS(startX, startY, goalX, goalY);

    cout << "Running DFS...\n";
    DFS(startX, startY, goalX, goalY);

    return 0;
}
