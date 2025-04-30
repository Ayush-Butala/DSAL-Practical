#include <iostream>
#include <string>

using namespace std;

const int MAX_CHILDREN = 10; // Maximum number of children per node

class Node
{
public:
    string name;
    Node *children[MAX_CHILDREN];
    int childCount;

    Node(string name)
    {
        this->name = name;
        this->childCount = 0;
        for (int i = 0; i < MAX_CHILDREN; i++)
        {
            children[i] = nullptr;
        }
    }

    void addChild(Node *child)
    {
        if (childCount < MAX_CHILDREN)
        {
            children[childCount++] = child;
        }
        else
        {
            cout << "Max children limit reached for " << name << endl;
        }
    }

    void printTree(int level = 0)
    {
        for (int i = 0; i < level; ++i)
            cout << "  ";
        cout << name << endl;
        for (int i = 0; i < childCount; ++i)
        {
            children[i]->printTree(level + 1);
        }
    }
};

int main()
{
    string bookName;
    cout << "Enter book name: ";
    getline(cin, bookName);
    Node *book = new Node(bookName);

    int numChapters;
    cout << "Enter number of chapters: ";
    cin >> numChapters;
    cin.ignore(); // Flush newline

    for (int i = 0; i < numChapters; ++i)
    {
        string chapterName;
        cout << "Enter name of Chapter " << i + 1 << ": ";
        getline(cin, chapterName);
        Node *chapter = new Node(chapterName);

        int numSections;
        cout << "Enter number of sections in " << chapterName << ": ";
        cin >> numSections;
        cin.ignore();

        for (int j = 0; j < numSections; ++j)
        {
            string sectionName;
            cout << "  Enter name of Section " << j + 1 << ": ";
            getline(cin, sectionName);
            Node *section = new Node(sectionName);

            int numSubsections;
            cout << "  Enter number of subsections in " << sectionName << ": ";
            cin >> numSubsections;
            cin.ignore();

            for (int k = 0; k < numSubsections; ++k)
            {
                string subsectionName;
                cout << "    Enter name of Subsection " << k + 1 << ": ";
                getline(cin, subsectionName);
                Node *subsection = new Node(subsectionName);
                section->addChild(subsection);
            }
            chapter->addChild(section);
        }
        book->addChild(chapter);
    }

    cout << "\n--- Book Structure ---\n";
    book->printTree();

    // Note: We’re not doing deep delete here to keep code simple.

    return 0;
}
