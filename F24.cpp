#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

typedef struct EMPLOYEE
{
    char name[20];
    char designation[20]; // Added designation
    int emp_id;
    int salary;
} Rec;

typedef struct INDEX
{
    int emp_id;
    int pos;
} Ind_Rec;

class EMP_CLASS
{
public:
    void Create();
    void Append();
    void Display();
    void Update();
    void Delete();
    void Search();
};

void EMP_CLASS::Create()
{
    Rec Records;
    Ind_Rec Index;
    ofstream file("EMP.DAT", ios::binary);
    ofstream ind("IND.DAT", ios::binary);

    char ch;
    int pos;
    do
    {
        cout << "\nEnter Name: ";
        cin >> Records.name;
        cout << "Enter Designation: ";
        cin >> Records.designation;
        cout << "Enter Emp_ID: ";
        cin >> Records.emp_id;
        cout << "Enter Salary: ";
        cin >> Records.salary;

        pos = (int)file.tellp();
        file.write((char *)&Records, sizeof(Records));

        Index.emp_id = Records.emp_id;
        Index.pos = pos;
        ind.write((char *)&Index, sizeof(Index));

        cout << "Do you want to add more records? (Y/N): ";
        cin >> ch;
    } while (ch == 'Y' || ch == 'y');

    file.close();
    ind.close();
}

void EMP_CLASS::Append()
{
    Rec Records;
    Ind_Rec Index;
    ofstream file("EMP.DAT", ios::app | ios::binary);
    ofstream ind("IND.DAT", ios::app | ios::binary);

    char ch;
    int pos;
    do
    {
        cout << "\nEnter Name: ";
        cin >> Records.name;
        cout << "Enter Designation: ";
        cin >> Records.designation;
        cout << "Enter Emp_ID: ";
        cin >> Records.emp_id;
        cout << "Enter Salary: ";
        cin >> Records.salary;

        pos = (int)file.tellp();
        file.write((char *)&Records, sizeof(Records));

        Index.emp_id = Records.emp_id;
        Index.pos = pos;
        ind.write((char *)&Index, sizeof(Index));

        cout << "Do you want to add more records? (Y/N): ";
        cin >> ch;
    } while (ch == 'Y' || ch == 'y');

    file.close();
    ind.close();
}

void EMP_CLASS::Display()
{
    Rec Records;
    Ind_Rec Index;
    ifstream file("EMP.DAT", ios::binary);
    ifstream ind("IND.DAT", ios::binary);

    while (ind.read((char *)&Index, sizeof(Index)))
    {
        file.seekg(Index.pos);
        file.read((char *)&Records, sizeof(Records));

        if (Records.emp_id != -1)
        {
            cout << "\nName: " << Records.name
                 << "\nDesignation: " << Records.designation
                 << "\nEmp_ID: " << Records.emp_id
                 << "\nSalary: " << Records.salary
                 << "\n---------------------------";
        }
    }

    file.close();
    ind.close();
}

void EMP_CLASS::Update()
{
    Rec Records;
    Ind_Rec Index;
    fstream file("EMP.DAT", ios::in | ios::out | ios::binary);
    ifstream ind("IND.DAT", ios::binary);
    int id, pos, flag = 0;

    cout << "Enter employee ID to update: ";
    cin >> id;

    while (ind.read((char *)&Index, sizeof(Index)))
    {
        if (id == Index.emp_id)
        {
            pos = Index.pos;
            file.seekg(pos);
            file.read((char *)&Records, sizeof(Records));

            cout << "Enter new Name: ";
            cin >> Records.name;
            cout << "Enter new Designation: ";
            cin >> Records.designation;
            cout << "Enter new Emp_ID: ";
            cin >> Records.emp_id;
            cout << "Enter new Salary: ";
            cin >> Records.salary;

            file.seekp(pos);
            file.write((char *)&Records, sizeof(Records));
            flag = 1;
            break;
        }
    }

    if (!flag)
    {
        cout << "Employee not found.\n";
    }

    file.close();
    ind.close();
}

void EMP_CLASS::Delete()
{
    Rec Records;
    Ind_Rec Index;
    fstream file("EMP.DAT", ios::in | ios::out | ios::binary);
    ifstream ind("IND.DAT", ios::binary);
    int id, pos, flag = 0;

    cout << "Enter employee ID to delete: ";
    cin >> id;

    while (ind.read((char *)&Index, sizeof(Index)))
    {
        if (id == Index.emp_id)
        {
            pos = Index.pos;
            file.seekg(pos);
            file.read((char *)&Records, sizeof(Records));

            Records.emp_id = -1; // Mark as deleted

            file.seekp(pos);
            file.write((char *)&Records, sizeof(Records));
            flag = 1;
            break;
        }
    }

    if (!flag)
    {
        cout << "Employee not found.\n";
    }

    file.close();
    ind.close();
}

void EMP_CLASS::Search()
{
    Rec Records;
    Ind_Rec Index;
    ifstream file("EMP.DAT", ios::binary);
    ifstream ind("IND.DAT", ios::binary);
    int id, flag = 0;

    cout << "Enter employee ID to search: ";
    cin >> id;

    while (ind.read((char *)&Index, sizeof(Index)))
    {
        if (id == Index.emp_id)
        {
            file.seekg(Index.pos);
            file.read((char *)&Records, sizeof(Records));

            if (Records.emp_id != -1)
            {
                cout << "\nName: " << Records.name
                     << "\nDesignation: " << Records.designation
                     << "\nEmp_ID: " << Records.emp_id
                     << "\nSalary: " << Records.salary;
            }
            else
            {
                cout << "Employee record is deleted.\n";
            }

            flag = 1;
            break;
        }
    }

    if (!flag)
    {
        cout << "Employee not found.\n";
    }

    file.close();
    ind.close();
}

int main()
{
    EMP_CLASS emp;
    int ch;

    do
    {
        cout << "\n===== MENU =====";
        cout << "\n1. Create";
        cout << "\n2. Append";
        cout << "\n3. Display";
        cout << "\n4. Update";
        cout << "\n5. Delete";
        cout << "\n6. Search";
        cout << "\n0. Exit";
        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            emp.Create();
            break;
        case 2:
            emp.Append();
            break;
        case 3:
            emp.Display();
            break;
        case 4:
            emp.Update();
            break;
        case 5:
            emp.Delete();
            break;
        case 6:
            emp.Search();
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (ch != 0);

    return 0;
}
