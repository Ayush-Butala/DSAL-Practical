#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Student
{
public:
    int roll;
    char name[30];
    char div;
    char address[50];

    void input()
    {
        cout << "Enter Roll: ";
        cin >> roll;
        cout << "Enter Name: ";
        cin.ignore(); // To ignore any leftover newline characters in the input buffer
        cin.getline(name, 30);
        cout << "Enter Division: ";
        cin >> div;
        cout << "Enter Address: ";
        cin.ignore();
        cin.getline(address, 50);
    }

    void display()
    {
        cout << roll << "\t" << name << "\t" << div << "\t" << address << endl;
    }
};

void addStudent()
{
    Student s;
    ofstream fout("students.dat", ios::app | ios::binary); // Open file in append mode
    s.input();
    fout.write((char *)&s, sizeof(Student)); // Write student data to file
    fout.close();
}

void displayAllStudents()
{
    Student s;
    ifstream fin("students.dat", ios::in | ios::binary); // Open file in read mode
    cout << "Roll\tName\tDiv\tAddress\n";
    while (fin.read((char *)&s, sizeof(Student)))
    {
        s.display();
    }
    fin.close();
}

void deleteStudent()
{
    int rollToDelete;
    cout << "Enter Roll number to delete: ";
    cin >> rollToDelete;

    Student s;
    ifstream fin("students.dat", ios::in | ios::binary);
    ofstream fout("temp.dat", ios::out | ios::binary); // Temporary file to store data after deletion

    bool found = false;
    while (fin.read((char *)&s, sizeof(Student)))
    {
        if (s.roll != rollToDelete)
        {
            fout.write((char *)&s, sizeof(Student)); // Write record to temp file if it's not to be deleted
        }
        else
        {
            found = true;
        }
    }
    fin.close();
    fout.close();

    // Replace original file with temp file
    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Student with roll " << rollToDelete << " deleted.\n";
    else
        cout << "Record not found.\n";
}

int main()
{
    int choice;
    do
    {
        cout << "\n1. Add student\n2. Display all students\n3. Delete student\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            displayAllStudents();
            break;
        case 3:
            deleteStudent();
            break;
        case 4:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 4);
    return 0;
}
