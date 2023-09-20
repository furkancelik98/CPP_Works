#include<iostream>
#include<fstream>
using namespace std;

class StudentRecord {
    string number, name, address, searchQuery, birthday; // Öğrenci kayıt bilgileri, arama sorgusu ve doğum tarihi
    fstream file; // Dosya işlemleri için kullanılacak nesne

public:
    void addStudent(); // Yeni öğrenci eklemek için kullanılır
    void viewAllStudents(); // Tüm öğrenci kayıtlarını görüntülemek için kullanılır
    void searchStudent(); // Öğrenci aramak için kullanılır
} obj;

int main() {
    char choice;

    cout << "1- Add Student" << endl;
    cout << "2- Show All Student Records" << endl;
    cout << "3- Search Student Record" << endl;
    cout << "4- Exit" << endl;

    cin >> choice;

    switch (choice) {
        case '1':
            cin.ignore();
            obj.addStudent();
            break;
        case '2':
            cin.ignore();
            obj.viewAllStudents();
            break;
        case '3':
            cin.ignore();
            obj.searchStudent();
            break;
        case '4':
            return 0;
        default:
            cout << "ERROR";
    }
}

void StudentRecord::addStudent() {
    cout << "Student Number : ";
    getline(cin, number);
    cout << "Student Name : ";
    getline(cin, name);
    cout << "Student Address : ";
    getline(cin, address);
    cout << "Student Birthday (MM/DD/YYYY) : ";
    getline(cin, birthday);

    file.open("Student_Record.txt", ios::out | ios::app);
    file << number << "*";
    file << name << "*";
    file << address << "*";
    file << birthday << endl;
    file.close();
}

void StudentRecord::viewAllStudents() {
    file.open("Student_Record.txt", ios::in);
    getline(file, number, '*');
    getline(file, name, '*');
    getline(file, address, '*');
    getline(file, birthday, '\n');
    
    while (!file.eof()) {
        cout << "\n";
        cout << "Student Number : " << number << endl;
        cout << "Student Name : " << name << endl;        
        cout << "Student Address : " << address << endl;
        cout << "Student Birthday : " << birthday << endl;

        getline(file, number, '*');
        getline(file, name, '*');
        getline(file, address, '*');
        getline(file, birthday, '\n');
    }
    file.close();
}

void StudentRecord::searchStudent() {
    cout << "Student Number : ";
    getline(cin, searchQuery);
    
    file.open("Student_Record.txt", ios::in);
    getline(file, number, '*');
    getline(file, name, '*');
    getline(file, address, '*');
    getline(file, birthday, '\n');
    
    while (!file.eof()) {
        if (number == searchQuery) {
            cout << endl;
            cout << "Student Number : " << number << endl;
            cout << "Student Name : " << name << endl;
            cout << "Student Address : " << address << endl;
            cout << "Student Birthday : " << birthday << endl;
        }
        getline(file, number, '*');
        getline(file, name, '*');
        getline(file, address, '*');
        getline(file, birthday, '\n');
    }
    file.close();
}
