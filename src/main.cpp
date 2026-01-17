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

bool containsChar(const char word[], char c) {
    for (int i = 0; word[i] != '\0'; i++)
        if (word[i] == c) return true;
    return false;
}

bool validWord(const char word[], int len) {
    if (strLen(word) != len) return false;
    for (int i = 0; word[i] != '\0'; i++)
        if (word[i] < 'a' || word[i] > 'z') return false;
    return true;
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

bool login(char loggedUser[], bool& isAdmin) {
    char u[30], p[30], role[10];
    char username[30], password[30];

    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    ifstream file("users.txt");
    while (file >> u >> p >> role) {
        if (strEqual(u, username) && strEqual(p, password)) {
            strCopy(loggedUser, u);
            isAdmin = strEqual(role, "admin");
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void getRandomWord(char chosen[]) {
    char words[1000][10];
    int count = 0;

    ifstream file("words.txt");
    if (!file) {
        cout << "words.txt not found!\n";
        exit(1);
    }

    while (file >> words[count]) count++;
    file.close();

    if (count == 0) {
        cout << "No words available!\n";
        exit(1);
    }

    int index = rand() % count;
    strCopy(chosen, words[index]);
}

void addWord() {
    char word[10];
    cout << "New word: ";
    cin >> word;

    ofstream file("words.txt", ios::app);
    file << word << endl;
    file.close();

    cout << "Word added.\n";
}

void adminMenu(const char user[]) {
    int choice;
    do {
        cout << "\n1. Add word\n2. Leaderboard\n3. Logout\nChoice: ";
        cin >> choice;

        if (choice == 1) addWord();
        else if (choice == 2) showLeaderboard();

    } while (choice != 3);
}

void userMenu(const char user[]) {
    int choice;
    do {
        cout << "\n1. Play\n2. Leaderboard\n3. Logout\nChoice: ";
        cin >> choice;

        if (choice == 1) playGame(user);
        else if (choice == 2) showLeaderboard();

    } while (choice != 3);
}

int main() {
    int choice;
    char loggedUser[30];
    bool isAdmin;

    do {
        cout << "\n1. Login\n2. Register\n3. Exit\nChoice: ";
        cin >> choice;

        if (choice == 2) registerUser();
        else if (choice == 1) {
            if (login(loggedUser, isAdmin)) {
                if (isAdmin) adminMenu(loggedUser);
                else userMenu(loggedUser);
            }
            else {
                cout << "Login failed! Either username or password is incorrect.\n";
            }
        }
    } while (choice != 3);

    return 0;
}