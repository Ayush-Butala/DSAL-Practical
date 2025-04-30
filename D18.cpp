#include <iostream>
#include <string>
using namespace std;

#define MAX 10

class OBST
{
    int n, p[MAX], q[MAX], w[MAX][MAX], c[MAX][MAX], r[MAX][MAX];
    string idnt[MAX];

public:
    void input();
    void build();
    void print(int i, int j, string parent = "None");
};

void OBST::input()
{
    cout << "Enter number of keys: ";
    cin >> n;
    cout << "Enter identifiers (sorted): ";
    for (int i = 1; i <= n; i++)
        cin >> idnt[i];
    cout << "Enter success probabilities: ";
    for (int i = 1; i <= n; i++)
        cin >> p[i];
    cout << "Enter failure probabilities: ";
    for (int i = 0; i <= n; i++)
        cin >> q[i];
}

void OBST::build()
{
    for (int i = 0; i <= n; i++)
    {
        w[i][i] = q[i];
        c[i][i] = 0;
        r[i][i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        int j = i + 1;
        w[i][j] = w[i][j - 1] + p[j] + q[j];
        c[i][j] = w[i][j];
        r[i][j] = j;
    }

    for (int m = 2; m <= n; m++)
    {
        for (int i = 0; i <= n - m; i++)
        {
            int j = i + m;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            int min = INT32_MAX, k = 0;
            for (int root = i + 1; root <= j; root++)
            {
                int cost = c[i][root - 1] + c[root][j];
                if (cost < min)
                {
                    min = cost;
                    k = root;
                }
            }
            c[i][j] = w[i][j] + min;
            r[i][j] = k;
        }
    }

    cout << "Root of OBST: " << idnt[r[0][n]] << "\n\n";
    print(0, n);
}

void OBST::print(int i, int j, string parent)
{
    if (i >= j)
        return;
    int root = r[i][j];
    cout << "Key: " << idnt[root] << ", Parent: " << parent << "\n";
    print(i, root - 1, idnt[root]);
    print(root, j, idnt[root]);
}

int main()
{
    OBST tree;
    tree.input();
    tree.build();
    return 0;
}
