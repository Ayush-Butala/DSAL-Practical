#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct TreeNode
{
    string key, meaning;
    TreeNode *left, *right;
    int height;
    TreeNode(string k, string m) : key(k), meaning(m), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree
{
private:
    TreeNode *root;

    int height(TreeNode *node)
    {
        return node ? node->height : 0;
    }

    void updateHeight(TreeNode *node)
    {
        node->height = max(height(node->left), height(node->right)) + 1;
    }

    int balanceFactor(TreeNode *node)
    {
        return height(node->left) - height(node->right);
    }

    TreeNode *rotateRight(TreeNode *y)
    {
        TreeNode *x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    TreeNode *rotateLeft(TreeNode *x)
    {
        TreeNode *y = x->right;
        x->right = y->left;
        y->left = x;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    TreeNode *balance(TreeNode *node)
    {
        updateHeight(node);
        int balance = balanceFactor(node);

        if (balance > 1)
        {
            if (balanceFactor(node->left) < 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1)
        {
            if (balanceFactor(node->right) > 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    TreeNode *insert(TreeNode *node, const string &key, const string &meaning)
    {
        if (!node)
            return new TreeNode(key, meaning);

        if (key < node->key)
            node->left = insert(node->left, key, meaning);
        else if (key > node->key)
            node->right = insert(node->right, key, meaning);
        else
            node->meaning = meaning; // Update meaning if the key exists

        return balance(node);
    }

    TreeNode *deleteNode(TreeNode *node, const string &key)
    {
        if (!node)
            return node;

        if (key < node->key)
            node->left = deleteNode(node->left, key);
        else if (key > node->key)
            node->right = deleteNode(node->right, key);
        else
        {
            if (!node->left || !node->right)
            {
                TreeNode *temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            TreeNode *temp = node->right;
            while (temp && temp->left)
                temp = temp->left;
            node->key = temp->key;
            node->meaning = temp->meaning;
            node->right = deleteNode(node->right, temp->key);
        }
        return balance(node);
    }

    void inorder(TreeNode *node)
    {
        if (node)
        {
            inorder(node->left);
            cout << node->key << " : " << node->meaning << endl;
            inorder(node->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(const string &key, const string &meaning)
    {
        root = insert(root, key, meaning);
    }

    void deleteKeyword(const string &key)
    {
        root = deleteNode(root, key);
    }

    void updateMeaning(const string &key, const string &newMeaning)
    {
        root = insert(root, key, newMeaning);
    }

    void display()
    {
        inorder(root);
    }

    string search(const string &key)
    {
        TreeNode *current = root;
        while (current)
        {
            if (key < current->key)
                current = current->left;
            else if (key > current->key)
                current = current->right;
            else
                return current->meaning;
        }
        return "Keyword not found";
    }

    int maxComparisons()
    {
        return height(root);
    }
};

int main()
{
    AVLTree dictionary;
    string key, meaning, newMeaning;
    int choice;

    while (true)
    {
        cout << "\nDictionary Menu:\n";
        cout << "1. Insert a new keyword\n";
        cout << "2. Delete a keyword\n";
        cout << "3. Update meaning of a keyword\n";
        cout << "4. Search for a keyword\n";
        cout << "5. Display dictionary\n";
        cout << "6. Find maximum comparisons needed for lookup\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "Enter keyword: ";
            getline(cin, key);
            cout << "Enter meaning: ";
            getline(cin, meaning);
            dictionary.insert(key, meaning);
            break;
        case 2:
            cout << "Enter keyword to delete: ";
            getline(cin, key);
            dictionary.deleteKeyword(key);
            break;
        case 3:
            cout << "Enter keyword to update: ";
            getline(cin, key);
            cout << "Enter new meaning: ";
            getline(cin, newMeaning);
            dictionary.updateMeaning(key, newMeaning);
            break;
        case 4:
            cout << "Enter keyword to search: ";
            getline(cin, key);
            cout << "Meaning: " << dictionary.search(key) << endl;
            break;
        case 5:
            cout << "Dictionary contents:\n";
            dictionary.display();
            break;
        case 6:
            cout << "Maximum comparisons needed for lookup: " << dictionary.maxComparisons() << endl;
            break;
        case 7:
            cout << "Exiting the program.\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
