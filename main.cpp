#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

struct User {
    int id;
    string username;
    string password;
};

vector<User> users;
int userIdCounter = 1;
const string filename = "users.txt";

void loadDataFromFile() {
    ifstream file(filename);
    if (file.is_open()) {
        User user;
        while (file >> user.id >> user.username >> user.password) {
            users.push_back(user);
            userIdCounter = max(userIdCounter, user.id + 1); // Ensure unique IDs
        }
        file.close();
    }
}

void saveDataToFile() {
    ofstream file(filename, ios::trunc);
    if (file.is_open()) {
        for (const auto &user : users) {
            file << user.id << " " << user.username << " " << user.password << endl;
        }
        file.close();
    }
}

void registerUser() {
    User newUser;
    newUser.id = userIdCounter++;
    cout << "Enter username: ";
    cin >> newUser.username;
    cout << "Enter password: ";
    cin >> newUser.password;
    users.push_back(newUser);
    saveDataToFile();
    cout << "User registered successfully!\n";
}

void loginUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (const auto &user : users) {
        if (user.username == username && user.password == password) {
            cout << "Login successful! Welcome, " << username << "!\n";
            return;
        }
    }
    cout << "Invalid username or password.\n";
}

void showUsers() {
    if (users.empty()) {
        cout << "No users registered yet.\n";
        return;
    }
    cout << "Registered Users:\n";
    for (const auto &user : users) {
        cout << "ID: " << user.id << " | Username: " << user.username << endl;
    }
}

void countUsers() {
    cout << "Total number of registered users: " << users.size() << endl;
}

void searchUser() {
    int searchId;
    cout << "Enter user ID to search: ";
    cin >> searchId;

    for (const auto &user : users) {
        if (user.id == searchId) {
            cout << "User found - ID: " << user.id << ", Username: " << user.username << endl;
            return;
        }
    }
    cout << "User not found.\n";
}

void deleteUser() {
    int deleteId;
    cout << "Enter user ID to delete: ";
    cin >> deleteId;

    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->id == deleteId) {
            users.erase(it);
            saveDataToFile();
            cout << "User deleted successfully.\n";
            return;
        }
    }
    cout << "User not found.\n";
}

void displayMenu() {
    cout << "\n=== Login Management System ===\n";
    cout << "1. Register User\n";
    cout << "2. Login User\n";
    cout << "3. Show All Users\n";
    cout << "4. Count Users\n";
    cout << "5. Search User\n";
    cout << "6. Delete User\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

int getChoice() {
    int choice;
    while (true) {
        if (cin >> choice && choice >= 1 && choice <= 7) {
            return choice;
        } else {
            cout << "Invalid input. Please enter a number between 1 and 7.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main() {
    loadDataFromFile(); // Load data at the start
    while (true) {
        displayMenu();
        int choice = getChoice();

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                showUsers();
                break;
            case 4:
                countUsers();
                break;
            case 5:
                searchUser();
                break;
            case 6:
                deleteUser();
                break;
            case 7:
                cout << "Exiting program.\n";
                return 0;
        }
    }
}
