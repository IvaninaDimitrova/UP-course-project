/**
*  
* Solution to course project # <09>
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Ivanina Dimitrova
* @idnumber <1MI0600686>
* @compiler GCC
*
* main file
*
*/

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

#define GREEN  "\033[32m"
#define YELLOW "\033[33m"
#define RESET  "\033[0m"

int strLen(const char s[]) {
    int i = 0;
    while (s[i] != '\0') i++;
    return i;
}

bool strEqual(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

void strCopy(char dest[], const char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void registerUser() {
    char username[30], password[30];

    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    file << username << " " << password << " user\n";
    file.close();

    cout << "Registration successful!\n";
}

bool login(char loggedUser[]) {
    char u[30], p[30];
    char username[30], password[30];

    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    ifstream file("users.txt");
    while (file >> u >> p) {
        if (strEqual(u, username) && strEqual(p, password)) {
            strCopy(loggedUser, u);
            return true;
        }
    }
    file.close();
    return false;
}

int main() {
    int choice;

    do {
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cout << "Choice: ";
        cin >> choice;
    } while (choice != 3);

    return 0;
}