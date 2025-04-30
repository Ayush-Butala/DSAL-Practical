#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    string name;
    int priority;
    Node *next;
    Node(string n, int p) : name(n), priority(p), next(nullptr) {}
};

class PriorityQueue
{
public:
    Node *front = nullptr;

    void insert(string name, int priority)
    {
        Node *newNode = new Node(name, priority);
        if (!front || front->priority < priority)
        {
            newNode->next = front;
            front = newNode;
        }
        else
        {
            Node *temp = front;
            while (temp->next && temp->next->priority >= priority)
                temp = temp->next;
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    void pop()
    {
        if (front)
        {
            Node *temp = front;
            front = front->next;
            delete temp;
        }
    }

    void display()
    {
        if (!front)
        {
            cout << "Queue is empty." << endl;
            return;
        }
        Node *temp = front;
        while (temp)
        {
            cout << temp->name << " with priority " << temp->priority << endl;
            temp = temp->next;
        }
    }
};

int main()
{
    PriorityQueue pq;
    int choice;
    string name;
    int priority;

    do
    {
        cout << "\n1. Add Patient\n2. Remove Patient\n3. Display Patients\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter patient name: ";
            cin >> ws; // To clear the input buffer
            getline(cin, name);
            cout << "Enter priority (3-High, 2-Medium, 1-Low): ";
            cin >> priority;
            pq.insert(name, priority);
            break;
        case 2:
            pq.pop();
            break;
        case 3:
            pq.display();
            break;
        case 0:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    return 0;
}
