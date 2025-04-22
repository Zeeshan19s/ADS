#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class Maze {
private:
    int rows, cols;
    int maze[100][100];

public:
    Maze(int r, int c) {
        rows = r;
        cols = c;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                maze[i][j] = 0; // 0 = path
    }

    void setWall(int x, int y) {
        maze[x][y] = 1; // 1 = wall
    }

    void printMaze() {
        cout << "\nMaze layout:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                cout << (maze[i][j] == 1 ? "#" : ".") << " ";
            cout << endl;
        }
    }

    void BFS(int sx, int sy) {
        bool visited[100][100] = {false};
        queue<pair<int, int>> q;

        visited[sx][sy] = true;
        q.push({sx, sy});

        cout << "\nBFS Traversal: ";
        while (!q.empty()) {
            pair<int, int> current = q.front(); q.pop();
            int x = current.first;
            int y = current.second;
            cout << "(" << x << "," << y << ") ";

            int dx[] = {-1, 1, 0, 0};
            int dy[] = {0, 0, -1, 1};

            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx >= 0 && ny >= 0 && nx < rows && ny < cols &&
                    !visited[nx][ny] && maze[nx][ny] == 0) {
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }
        cout << endl;
    }

    void DFS(int sx, int sy) {
        bool visited[100][100] = {false};
        stack<pair<int, int>> s;

        visited[sx][sy] = true;
        s.push({sx, sy});

        cout << "\nDFS Traversal: ";
        while (!s.empty()) {
            pair<int, int> current = s.top(); s.pop();
            int x = current.first;
            int y = current.second;
            cout << "(" << x << "," << y << ") ";

            int dx[] = {-1, 1, 0, 0};
            int dy[] = {0, 0, -1, 1};

            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx >= 0 && ny >= 0 && nx < rows && ny < cols &&
                    !visited[nx][ny] && maze[nx][ny] == 0) {
                    visited[nx][ny] = true;
                    s.push({nx, ny});
                }
            }
        }
        cout << endl;
    }
};

int main() {
    int rows, cols;
    int choice;
    Maze m(0, 0);

    while (true) {
        cout << "\nMaze Traversal Program\n";
        cout << "1. Set Maze Size\n";
        cout << "2. Set Walls\n";
        cout << "3. Print Maze\n";
        cout << "4. Run BFS\n";
        cout << "5. Run DFS\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter maze size (rows cols): ";
                cin >> rows >> cols;
                m = Maze(rows, cols); // Create new maze object with the input size
                break;

            case 2:
                int w;
                cout << "Enter number of walls: ";
                cin >> w;

                cout << "Enter wall positions (x y):\n";
                for (int i = 0; i < w; i++) {
                    int x, y;
                    cin >> x >> y;
                    m.setWall(x, y);
                }
                break;

            case 3:
                m.printMaze();
                break;

            case 4:
                int sx_bfs, sy_bfs;
                cout << "Enter starting position for BFS (x y): ";
                cin >> sx_bfs >> sy_bfs;
                m.BFS(sx_bfs, sy_bfs);
                break;

            case 5:
                int sx_dfs, sy_dfs;
                cout << "Enter starting position for DFS (x y): ";
                cin >> sx_dfs >> sy_dfs;
                m.DFS(sx_dfs, sy_dfs);
                break;

            case 6:
                cout << "Exiting program.\n";
                return 0;

            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    }
}