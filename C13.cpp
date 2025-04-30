#include <iostream>
#include <queue>
#include <map>
#include <vector>
using namespace std;

const int MAX = 10;

// List of landmark names
string landmarks[MAX] = {
    "Main Gate", "Library", "Canteen", "Auditorium", "Computer Lab",
    "Hostel", "Playground", "Admin Block", "Parking", "Workshop"};

int total_vertices;

class Graph
{
    int adjMatrix[MAX][MAX];  // For DFS
    vector<int> adjList[MAX]; // For BFS

public:
    void createGraph()
    {
        cout << "Enter number of landmarks (max 10): ";
        cin >> total_vertices;

        // Adjacency Matrix input
        cout << "\nEnter adjacency matrix:\n";
        for (int i = 0; i < total_vertices; i++)
        {
            for (int j = 0; j < total_vertices; j++)
            {
                cin >> adjMatrix[i][j];
                if (adjMatrix[i][j])
                {
                    adjList[i].push_back(j); // Create adjacency list too
                }
            }
        }
    }

    void dfsTraversal(int start)
    {
        vector<bool> visited(total_vertices, false);
        vector<int> stack;
        stack.push_back(start);

        cout << "\nDFS Traversal: ";
        while (!stack.empty())
        {
            int curr = stack.back();
            stack.pop_back();

            if (!visited[curr])
            {
                cout << landmarks[curr] << " ";
                visited[curr] = true;

                // Push neighbors in reverse order (to simulate left-to-right visit)
                for (int i = total_vertices - 1; i >= 0; --i)
                {
                    if (adjMatrix[curr][i] && !visited[i])
                    {
                        stack.push_back(i);
                    }
                }
            }
        }
        cout << endl;
    }

    void bfsTraversal(int start)
    {
        vector<bool> visited(total_vertices, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        cout << "\nBFS Traversal: ";
        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            cout << landmarks[curr] << " ";

            for (int neighbor : adjList[curr])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    void showLandmarks()
    {
        cout << "\nAvailable Landmarks:\n";
        for (int i = 0; i < total_vertices; i++)
        {
            cout << i << ": " << landmarks[i] << endl;
        }
    }
};

int main()
{
    Graph g;
    g.createGraph();
    g.showLandmarks();

    int start;
    cout << "\nEnter start landmark index for DFS and BFS: ";
    cin >> start;

    g.dfsTraversal(start);
    g.bfsTraversal(start);

    return 0;
}
