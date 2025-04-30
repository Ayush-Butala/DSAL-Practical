#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

struct node
{
    char data;
    node *left;
    node *right;
};

class tree
{
public:
    node *root;

    tree() : root(nullptr) {}

    void expression(const char *prefix)
    {
        stack<node *> s;
        for (int i = strlen(prefix) - 1; i >= 0; i--)
        {
            node *newNode = new node{prefix[i], nullptr, nullptr};

            if (isalpha(prefix[i]))
            {
                s.push(newNode);
            }
            else
            {
                newNode->left = s.top();
                s.pop();
                newNode->right = s.top();
                s.pop();
                s.push(newNode);
            }
        }
        root = s.top();
        s.pop();
    }

    void non_rec_postorder(node *root)
    {
        if (!root)
            return;

        stack<pair<node *, bool>> s;
        s.push({root, false});

        while (!s.empty())
        {
            node *current = s.top().first;
            bool visited = s.top().second;
            s.pop();

            if (visited)
            {
                cout << current->data;
            }
            else
            {
                s.push({current, true});
                if (current->right)
                    s.push({current->right, false});
                if (current->left)
                    s.push({current->left, false});
            }
        }
        cout << endl;
    }

    void delete_tree(node *root)
    {
        if (!root)
            return;
        delete_tree(root->left);
        delete_tree(root->right);
        cout << "Deleting node: " << root->data << endl;
        delete root;
    }
};

int main()
{
    tree t;
    char exp[20];

    int choice;
    do
    {
        cout << "1 -> Enter prefix expression" << endl;
        cout << "2 -> Display postorder expression" << endl;
        cout << "3 -> Deletion" << endl;
        cout << "4 -> Exit" << endl;
        cout << "Choose an option (1-4): ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "Enter prefix expression (e.g., +--a*bc/def): ";
            cin >> exp;
            t.expression(exp);
            break;
        case 2:
            cout << "Postorder expression: ";
            t.non_rec_postorder(t.root);
            break;
        case 3:
            t.delete_tree(t.root);
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 4);

    return 0;
}
