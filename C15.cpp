#include <iostream>
using namespace std;
class PrimMST
{
private:
    static const int MAX = 10;
    int n;
    int cost[MAX][MAX];
    int visit[MAX];
    int mincost;

public:
    PrimMST(int vertices)
    {
        if (vertices > MAX)
        {
            cout << "Error: Maximum number of vertices exceeded!\n";
            exit(1);
        }
        n = vertices;
        mincost = 0;

        for (int i = 0; i < MAX; i++)
            for (int j = 0; j < MAX; j++)
                cost[i][j] = -1;

        for (int i = 0; i < MAX; i++)
            visit[i] = 0;
    }

    void inputGraph()
    {
        char op;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                cout << "Do you want an edge between " << i + 1 << " and " << j + 1
                     << "? (y/n): ";
                cin >> op;
                if (op == 'y' || op == 'Y')
                {
                    cout << "Enter weight: ";
                    cin >> cost[i][j];
                    cost[j][i] = cost[i][j];
                }
            }
        }
    }

    void computeMST()
    {
        visit[0] = 1;
        for (int k = 0; k < n - 1; k++)
        {
            int min = 999, row = -1, col = -1;
            for (int i = 0; i < n; i++)
            {
                if (visit[i] == 1)
                {
                    for (int j = 0; j < n; j++)
                    {
                        if (visit[j] == 0 && cost[i][j] != -1 && cost[i][j] < min)
                        {
                            min = cost[i][j];
                            row = i;
                            col = j;
                        }
                    }
                }
            }
            if (min == 999)
            {
                cout << "\nGraph is disconnected! MST cannot be formed.\n";
                return;
            }
            mincost += min;
            visit[col] = 1;
            cost[row][col] = cost[col][row] = -1;
            cout << row + 1 << " -> " << col + 1 << " (Cost: " << min << ")" << endl;
        }
        cout << "\nMinimum Cost of MST: " << mincost << endl;
    }
};
int main()
{
    int vertices;
    cout << "Enter number of vertices (max 10): ";
    cin >> vertices;
    PrimMST mst(vertices);
    mst.inputGraph();
    mst.computeMST();
    return 0;
}