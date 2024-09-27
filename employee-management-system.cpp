#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>

using namespace std;

class Employee {
protected:
    string name, roll_no, phoneNumber, email, personalNumber;

public:
    void menu();
    void insertEmployee();
    void searchEmployee();
    void viewAllEmployees();
    void deleteEmployee();
};

// Inheritance for different employee types

class Manager : public Employee {
public:
    int levelOfEducation; 
    string specialty;
    double monthlySalary;

    void getManagerDetails() {
        do {
            cout << "\t\t\t Enter Employee's level of education (1-10): ";
            cin >> levelOfEducation;
        } while (levelOfEducation < 1 || levelOfEducation > 10);

        // Specialty options
        vector<string> specialties = {
            "Finance", "Marketing", "Human Resources", "IT", "Sales",
            "Operations", "Legal", "Customer Service", "Research", "Administration"
        };
        cout << "\t\t\t Choose a Specialty: \n";
        for (size_t i = 0; i < specialties.size(); ++i) {
            cout << "\t\t\t " << (i + 1) << ". " << specialties[i] << "\n";
        }
        int specialtyChoice;
        do {
            cout << "\t\t\t Enter your choice (1-" << specialties.size() << "): ";
            cin >> specialtyChoice;
        } while (specialtyChoice < 1 || specialtyChoice > specialties.size());
        specialty = specialties[specialtyChoice - 1];

        cout << "\t\t\t Enter Monthly Salary: ";
        cin >> monthlySalary;
    }

    void displayDetails() const {
        cout << "Level of Education: " << levelOfEducation << "\n";
        cout << "Specialty: " << specialty << "\n";
        cout << "Monthly Salary: " << monthlySalary << "\n";
    }
};

class Teacher : public Employee {
public:
    string subjects[4];
    int studentGrades[4]; // Grades for 4 students
    double hourlySalary;

    void getTeacherDetails() {
        // Subjects options
        vector<string> subjectOptions = {
            "Math", "Science", "English", "History", "Geography",
            "Physical Education", "Art", "Music", "Computer Science", "Biology"
        };

        cout << "\t\t\t Choose 4 Subjects (1-" << subjectOptions.size() << "): \n";
        for (size_t i = 0; i < subjectOptions.size(); ++i) {
            cout << "\t\t\t " << (i + 1) << ". " << subjectOptions[i] << "\n";
        }

        for (int i = 0; i < 4; ++i) {
            int subjectChoice;
            bool validChoice = false;
            while (!validChoice) {
                cout << "\t\t\t Enter your choice for subject " << (i + 1) << ": ";
                cin >> subjectChoice;

                // Check if input is valid
                if (cin.fail() || subjectChoice < 1 || subjectChoice > subjectOptions.size()) {
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "Invalid choice. Please select a valid subject number (1-" << subjectOptions.size() << ").\n";
                } else {
                    subjects[i] = subjectOptions[subjectChoice - 1]; // Store the selected subject
                    validChoice = true; // Mark as valid choice to break the loop
                }
            }
        }

        for (int i = 0; i < 4; ++i) {
            int grade;
            bool validGrade = false;
            while (!validGrade) {
                cout << "\t\t\t Enter grade for student " << (i + 1) << " (1-20): ";
                cin >> grade;

                // Check if input is valid
                if (cin.fail() || grade < 1 || grade > 20) {
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "Invalid grade. Please enter a value between 1 and 20.\n";
                } else {
                    studentGrades[i] = grade; // Store the valid grade
                    validGrade = true; // Mark as valid grade to break the loop
                }
            }
        }

        cout << "\t\t\t Enter Hourly Salary: ";
        cin >> hourlySalary;
    }

    void displayDetails() const {
        cout << "Subjects Taught: ";
        for (int i = 0; i < 4; ++i) {
            cout << subjects[i];
            if (i < 3) cout << ", "; 
        }
        cout << "\nGrades: ";
        for (int i = 0; i < 4; ++i) {
            cout << studentGrades[i];
            if (i < 3) cout << ", "; 
        }
        cout << "\nHourly Salary: " << hourlySalary << "\n";
    }
};

// Menu for employee management

void Employee::menu() {
    int choice;
    char x;

    do {
        cout << "\t\t\t ** Employee Management System ** \n";
        cout << "\t\t\t 1. Insert Employee Record\n";
        cout << "\t\t\t 2. View All Employees\n";
        cout << "\t\t\t 3. Search Employee\n";
        cout << "\t\t\t 4. Delete Employee\n";
        cout << "\t\t\t 5. Exit\n";
        cout << "\t\t\t Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            insertEmployee();
            break;
        case 2:
            viewAllEmployees();
            break;
        case 3:
            searchEmployee();
            break;
        case 4:
            deleteEmployee();
            break;
        case 5:
            cout << "\t\t\t Exiting the program...\n";
            return;
        default:
            cout << "\t\t\t Invalid choice. Please try again.\n";
        }

        cout << "\t\t\t Do you want to continue? (Y/N): ";
        cin >> x;

    } while (x == 'Y' || x == 'y');
}

void Employee::insertEmployee() {
    fstream file;
    char type;
    cout << "\t\t\tEnter Employee Type (M for Manager, T for Teacher): ";
    cin >> type;

    cout << "\t\t\tEnter Name: ";
    cin.ignore(); 
    getline(cin, name); 
    cout << "\t\t\tEnter Roll No.: ";
    cin >> roll_no;
    cout << "\t\t\tEnter Phone Number: ";
    cin >> phoneNumber;
    cout << "\t\t\tEnter Email: ";
    cin >> email;
    cout << "\t\t\tEnter Personal No.: ";
    cin >> personalNumber;

    // Open file to append new employee record
    file.open("EmployeeRecord.txt", ios::app);
    if (file.is_open()) {
        if (type == 'M' || type == 'm') {
            Manager manager;
            manager.name = name;  
            manager.roll_no = roll_no; 
            manager.phoneNumber = phoneNumber; 
            manager.email = email; 
            manager.personalNumber = personalNumber; 
            manager.getManagerDetails();
            file << "Manager: " << manager.name << " " << manager.roll_no << " " 
                 << manager.phoneNumber << " " << manager.email << " " << manager.personalNumber 
                 << " " << manager.monthlySalary << " " << manager.levelOfEducation << " " 
                 << manager.specialty << "\n"; // Store all manager details
        } else if (type == 'T' || type == 't') {
            Teacher teacher;
            teacher.name = name; 
            teacher.roll_no = roll_no; 
            teacher.phoneNumber = phoneNumber; 
            teacher.email = email; 
            teacher.personalNumber = personalNumber; 
            teacher.getTeacherDetails();
            file << "Teacher: " << teacher.name << " " << teacher.roll_no << " " 
                 << teacher.phoneNumber << " " << teacher.email << " " << teacher.personalNumber 
                 << " " << teacher.hourlySalary << " ";
            for (int i = 0; i < 4; ++i) {
                file << teacher.subjects[i];
                if (i < 3) file << ", "; 
            }
            file << " ";
            for (int i = 0; i < 4; ++i) {
                file << teacher.studentGrades[i];
                if (i < 3) file << ", "; 
            }
            file << "\n";
        } else {
            cout << "Invalid employee type. Please enter either 'M' or 'T'.\n";
        }
        file.close();
        cout << "\n\t\t\t Employee Record Inserted Successfully...\n";
    } else {
        cout << "\n\t\t\t Unable to Open File...\n";
    }
}

void Employee::viewAllEmployees() {
    fstream file;
    cout << "\n------------------------------------- Employee Record Table --------------------------------------------\n";
    
    file.open("EmployeeRecord.txt", ios::in);
    if (!file) {
        cout << "\n\t\t\tNo Data is Present or Unable to Open File...\n"; 
        return;
    }

    string line;
    bool hasData = false; // To check if there's any data
    while (getline(file, line)) {
        hasData = true; // Set to true if any line is read

        // Example line format for parsing
        stringstream ss(line);
        string type;

        ss >> type; // Read the employee type

        cout << "-----------------------------------------\n";
        cout << "Employee Type: " << type << "\n";

        if (type == "Manager:") {
            Manager manager;
            ss >> manager.name >> manager.roll_no >> manager.phoneNumber >> manager.email 
               >> manager.personalNumber >> manager.monthlySalary >> manager.levelOfEducation 
               >> manager.specialty;

            cout << "Roll No: " << manager.roll_no << "\n";
            cout << "Name: " << manager.name << "\n";
            cout << "Phone Number: " << manager.phoneNumber << "\n";
            cout << "Email: " << manager.email << "\n";
            cout << "Personal No.: " << manager.personalNumber << "\n";
            manager.displayDetails();
        } else if (type == "Teacher:") {
            Teacher teacher;
            ss >> teacher.name >> teacher.roll_no >> teacher.phoneNumber >> teacher.email 
               >> teacher.personalNumber >> teacher.hourlySalary;

            // Read subjects
            for (int i = 0; i < 4; ++i) {
                ss >> teacher.subjects[i];
            }

            // Read grades
            for (int i = 0; i < 4; ++i) {
                ss >> teacher.studentGrades[i];
            }

            cout << "Roll No: " << teacher.roll_no << "\n";
            cout << "Name: " << teacher.name << "\n";
            cout << "Phone Number: " << teacher.phoneNumber << "\n";
            cout << "Email: " << teacher.email << "\n";
            cout << "Personal No.: " << teacher.personalNumber << "\n";
            teacher.displayDetails();
        }

        cout << "-----------------------------------------\n";
    }

    if (!hasData) {
        cout << "\n\t\t\tNo Employees Found...\n"; 
    }

    file.close();
}

void Employee::searchEmployee() {
    fstream file;
    string roll_no;
    cout << "\t\t\tEnter Roll No. to Search: ";
    cin >> roll_no;

    file.open("EmployeeRecord.txt", ios::in);
    if (!file) {
        cout << "\n\t\t\tNo Data Found or Unable to Open File...\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line.find(roll_no) != string::npos) { // Check if roll_no is in the line
            cout << "\n-----------------------------------------\n";
            cout << "Employee Record Found:\n";
            
            // Example line format for parsing
            stringstream ss(line);
            string type;

            ss >> type; // Read the employee type

            cout << "Employee Type: " << type << "\n";

            if (type == "Manager:") {
                Manager manager;
                ss >> manager.name >> manager.roll_no >> manager.phoneNumber >> manager.email 
                   >> manager.personalNumber >> manager.monthlySalary >> manager.levelOfEducation 
                   >> manager.specialty;

                cout << "Roll No: " << manager.roll_no << "\n";
                cout << "Name: " << manager.name << "\n";
                cout << "Phone Number: " << manager.phoneNumber << "\n";
                cout << "Email: " << manager.email << "\n";
                cout << "Personal No.: " << manager.personalNumber << "\n";
                manager.displayDetails();
            } else if (type == "Teacher:") {
                Teacher teacher;
                ss >> teacher.name >> teacher.roll_no >> teacher.phoneNumber >> teacher.email 
                   >> teacher.personalNumber >> teacher.hourlySalary;

                // Read subjects
                for (int i = 0; i < 4; ++i) {
                    ss >> teacher.subjects[i];
                }

                // Read grades
                for (int i = 0; i < 4; ++i) {
                    ss >> teacher.studentGrades[i];
                }

                cout << "Roll No: " << teacher.roll_no << "\n";
                cout << "Name: " << teacher.name << "\n";
                cout << "Phone Number: " << teacher.phoneNumber << "\n";
                cout << "Email: " << teacher.email << "\n";
                cout << "Personal No.: " << teacher.personalNumber << "\n";
                teacher.displayDetails();
            }

            cout << "-----------------------------------------\n";
            found = true;
            break; // Stop searching after finding the record
        }
    }

    if (!found) {
        cout << "\n\t\t\t No Employee Record Found with Roll No.: " << roll_no << "\n";
    }

    file.close();
}

void Employee::deleteEmployee() {
    fstream file, temp;
    string roll_no;
    cout << "\t\t\tEnter Roll No. to Delete: ";
    cin >> roll_no;

    file.open("EmployeeRecord.txt", ios::in);
    if (!file) {
        cout << "\n\t\t\tNo Data Found or Unable to Open File...\n";
        return;
    }

    temp.open("temp.txt", ios::out);
    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line.find(roll_no) == string::npos) { // If line doesn't contain roll_no
            temp << line << "\n"; // Write it to temp file
        } else {
            found = true; // Record found
        }
    }

    if (found) {
        cout << "\n\t\t\t Employee Record Deleted Successfully...\n";
    } else {
        cout << "\n\t\t\t No Employee Record Found with Roll No.: " << roll_no << "\n";
    }

    file.close();
    temp.close();

    // Remove old file and rename temp file to original file
    remove("EmployeeRecord.txt");
    rename("temp.txt", "EmployeeRecord.txt");
}

int main() {
    Employee emp;
    emp.menu(); // Call the menu function
    return 0;
}
