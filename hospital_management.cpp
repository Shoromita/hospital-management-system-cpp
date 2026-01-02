
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* ---------- GLOBAL BED INFO ---------- */
int totalBeds = 50;
int availableBeds = 30;

/* ---------- USER ---------- */
class User {
public:
    string username, password;

    void registerUser() {
        ofstream file("users.txt", ios::app);
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        file << username << " " << password << endl;
        file.close();
        cout << "User registered successfully!\n";
    }

    bool loginUser() {
        string u, p;
        cout << "Username: ";
        cin >> u;
        cout << "Password: ";
        cin >> p;

        ifstream file("users.txt");
        while (file >> username >> password) {
            if (u == username && p == password) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
};

/* ---------- DOCTOR ---------- */
class Doctor {
public:
    string name, specialization, degree, availability, username, password;

    void registerDoctor() {
        ofstream file("doctors.txt", ios::app);
        cout << "Doctor Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Specialization: ";
        getline(cin, specialization);
        cout << "Degree: ";
        getline(cin, degree);
        cout << "Availability (Yes/No): ";
        getline(cin, availability);
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        file << name << "|" << specialization << "|" << degree << "|"
             << availability << "|" << username << "|" << password << endl;
        file.close();
        cout << "Doctor registered successfully!\n";
    }

    static void viewDoctors() {
        ifstream file("doctors.txt");
        Doctor d;
        cout << "\n--- Doctor List ---\n";
        while (getline(file, d.name, '|')) {
            getline(file, d.specialization, '|');
            getline(file, d.degree, '|');
            getline(file, d.availability, '|');
            getline(file, d.username, '|');
            getline(file, d.password);

            cout << "\nName: " << d.name
                 << "\nSpecialization: " << d.specialization
                 << "\nDegree: " << d.degree
                 << "\nAvailable: " << d.availability << "\n";
        }
        file.close();
    }
};

/* ---------- PATIENT ---------- */
class Patient {
public:
    int id;
    string name, disease;

    void addPatient() {
        ofstream file("patients.txt", ios::app);
        cout << "Patient ID: ";
        cin >> id;
        cin.ignore();
        cout << "Name: ";
        getline(cin, name);
        cout << "Disease: ";
        getline(cin, disease);

        file << id << "|" << name << "|" << disease << endl;
        file.close();
        cout << "Patient added successfully!\n";
    }

    static void viewPatients() {
        ifstream file("patients.txt");
        Patient p;
        cout << "\n--- Patient List ---\n";
        while (file >> p.id) {
            file.ignore();
            getline(file, p.name, '|');
            getline(file, p.disease);
            cout << "\nID: " << p.id
                 << "\nName: " << p.name
                 << "\nDisease: " << p.disease << "\n";
        }
        file.close();
    }
};

/* ---------- MENUS ---------- */
void userMenu() {
    User u;
    int ch;
    cout << "\n1. Register\n2. Login\nChoice: ";
    cin >> ch;

    if (ch == 1)
        u.registerUser();
    else if (ch == 2) {
        if (u.loginUser()) {
            cout << "\nLogin successful!\n";
            Doctor::viewDoctors();
            cout << "\nAvailable Beds: " << availableBeds << "/" << totalBeds << endl;
        } else
            cout << "Login failed!\n";
    }
}

void doctorMenu() {
    Doctor d;
    int ch;
    cout << "\n1. Register\n2. Login\nChoice: ";
    cin >> ch;

    if (ch == 1)
        d.registerDoctor();
    else if (ch == 2) {
        string u, p;
        cout << "Username: ";
        cin >> u;
        cout << "Password: ";
        cin >> p;

        ifstream file("doctors.txt");
        bool found = false;
        while (getline(file, d.name, '|')) {
            getline(file, d.specialization, '|');
            getline(file, d.degree, '|');
            getline(file, d.availability, '|');
            getline(file, d.username, '|');
            getline(file, d.password);

            if (u == d.username && p == d.password) {
                found = true;
                break;
            }
        }
        file.close();

        if (found) {
            cout << "\nDoctor login successful!\n";
            Patient::viewPatients();
        } else
            cout << "Login failed!\n";
    }
}

void adminMenu() {
    Patient p;
    Doctor d;
    int ch;
    do {
        cout << "\n--- Admin Menu ---";
        cout << "\n1. Add Patient";
        cout << "\n2. Add Doctor";
        cout << "\n3. Change Bed Availability";
        cout << "\n4. View Patients";
        cout << "\n5. View Doctors";
        cout << "\n6. Back";
        cout << "\nChoice: ";
        cin >> ch;

        if (ch == 1) p.addPatient();
        else if (ch == 2) d.registerDoctor();
        else if (ch == 3) {
            cout << "Enter available beds: ";
            cin >> availableBeds;
        }
        else if (ch == 4) Patient::viewPatients();
        else if (ch == 5) Doctor::viewDoctors();
    } while (ch != 6);
}

/* ---------- MAIN ---------- */
int main() {
    int choice;
    do {
        cout << "\n=== Hospital Management System ===";
        cout << "\n1. User";
        cout << "\n2. Doctor";
        cout << "\n3. Admin";
        cout << "\n4. Exit";
        cout << "\nChoice: ";
        cin >> choice;

        if (choice == 1) userMenu();
        else if (choice == 2) doctorMenu();
        else if (choice == 3) adminMenu();
    } while (choice != 4);

    return 0;
}
