#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

string filename = "students.txt";

struct Student {
    int id;
    string name;
    int age;
    float marks;
};

bool idExists(int searchId) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        int id = stoi(line.substr(0, line.find(',')));

        if (id == searchId) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void addStudent() {
    Student s;

    cout << "\nEnter Student ID: ";
    cin >> s.id;

    if (idExists(s.id)) {
        cout << "\nStudent ID already exists!\n";
        return;
    }

    cin.ignore();

    cout << "Enter Student Name: ";
    getline(cin, s.name);

    cout << "Enter Age: ";
    cin >> s.age;

    cout << "Enter Marks: ";
    cin >> s.marks;

    ofstream file(filename, ios::app);

    file << s.id << ","
         << s.name << ","
         << s.age << ","
         << s.marks << endl;

    file.close();

    cout << "\nStudent Added Successfully!\n";
}

void displayStudents() {
    ifstream file(filename);
    string line;

    cout << "\n========================================\n";
    cout << "          STUDENT RECORDS\n";
    cout << "========================================\n";

    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

void searchStudent() {
    int searchId;
    string line;
    bool found = false;

    cout << "\nEnter Student ID to Search: ";
    cin >> searchId;

    ifstream file(filename);

    while (getline(file, line)) {
        int id = stoi(line.substr(0, line.find(',')));

        if (id == searchId) {
            cout << "\nStudent Found:\n";
            cout << line << endl;
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nStudent Not Found!\n";
}

void updateStudent() {
    int updateId;
    string line;
    bool found = false;

    cout << "\nEnter Student ID to Update: ";
    cin >> updateId;

    ifstream file(filename);
    ofstream temp("temp.txt");

    while (getline(file, line)) {
        int id = stoi(line.substr(0, line.find(',')));

        if (id == updateId) {
            Student s;

            cin.ignore();

            cout << "Enter New Name: ";
            getline(cin, s.name);

            cout << "Enter New Age: ";
            cin >> s.age;

            cout << "Enter New Marks: ";
            cin >> s.marks;

            temp << updateId << ","
                 << s.name << ","
                 << s.age << ","
                 << s.marks << endl;

            found = true;
        }
        else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (found)
        cout << "\nStudent Updated Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

void deleteStudent() {
    int deleteId;
    string line;
    bool found = false;

    cout << "\nEnter Student ID to Delete: ";
    cin >> deleteId;

    ifstream file(filename);
    ofstream temp("temp.txt");

    while (getline(file, line)) {
        int id = stoi(line.substr(0, line.find(',')));

        if (id == deleteId) {
            found = true;
            continue;
        }

        temp << line << endl;
    }

    file.close();
    temp.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (found)
        cout << "\nStudent Deleted Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n=================================\n";
        cout << "   STUDENT MANAGEMENT SYSTEM\n";
        cout << "=================================\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter Choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                cout << "\nThank You!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}
