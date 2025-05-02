#include <iostream>
#include <string>
using namespace std;

struct Node
{
    string key, meaning;
    Node *left, *right;

    Node(string k, string m) : key(k), meaning(m), left(nullptr), right(nullptr) {}
};

class Dictionary
{
    Node *root = nullptr;

    Node *insert(Node *node, string key, string meaning)
    {
        if (!node)
            return new Node(key, meaning);
        if (key < node->key)
            node->left = insert(node->left, key, meaning);
        else
            node->right = insert(node->right, key, meaning);
        return node;
    }

    void display(Node *node)
    {
        if (!node)
            return;
        display(node->left);
        cout << node->key << " : " << node->meaning << endl;
        display(node->right);
    }

    Node *search(Node *node, string key, int &cmp)
    {
        while (node)
        {
            cmp++;
            if (key == node->key)
                return node;

            if (key < node->key)
                node = node->left;
            else
                node = node->right;
        }
        return nullptr;
    }

    Node *findMin(Node *node)
    {
        if (node)
        {
            while (node->left)
                node = node->left;
        }
        return node;
    }

    Node *deleteNode(Node *node, string key)
    {
        if (!node)
            return nullptr;
        if (key < node->key)
            node->left = deleteNode(node->left, key);
        else if (key > node->key)
            node->right = deleteNode(node->right, key);
        else
        {
            if (!node->left)
                return node->right;
            if (!node->right)
                return node->left;
            Node *minNode = findMin(node->right);
            node->key = minNode->key;
            node->meaning = minNode->meaning;
            node->right = deleteNode(node->right, minNode->key);
        }
        return node;
    }

public:
    void add()
    {
        string key, meaning;
        cout << "Enter keyword: ";
        cin >> key;
        cout << "Enter meaning: ";
        cin.ignore();
        getline(cin, meaning);
        root = insert(root, key, meaning);
    }

    void show()
    {
        if (!root)
            cout << "Dictionary is empty.\n";
        else
            display(root);
    }

    void find()
    {
        string key;
        cout << "Enter keyword to search: ";
        cin >> key;
        int cmp = 0;
        Node *result = search(root, key, cmp);
        if (result)
            cout << "Found: " << result->meaning << " (Comparisons: " << cmp << ")\n";
        else
            cout << "Keyword not found.\n";
    }

    void update()
    {
        string key;
        cout << "Enter keyword to update: ";
        cin >> key;
        int cmp = 0;
        Node *result = search(root, key, cmp);
        if (result)
        {
            cout << "Enter new meaning: ";
            cin >> result->meaning;
            cout << "Meaning updated.\n";
        }
        else
            cout << "Keyword not found.\n";
    }

    void remove()
    {
        string key;
        cout << "Enter keyword to delete: ";
        cin >> key;
        root = deleteNode(root, key);
        cout << "If keyword existed, it was removed.\n";
    }
};

int main()
{
    Dictionary dict;
    int choice;

    do
    {
        cout << "\n1. Add\n2. Display\n3. Search\n4. Update\n5. Delete\n0. Exit\nChoose: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            dict.add();
            break;
        case 2:
            dict.show();
            break;
        case 3:
            dict.find();
            break;
        case 4:
            dict.update();
            break;
        case 5:
            dict.remove();
            break;
        }
    } while (choice != 0);

    return 0;
}
