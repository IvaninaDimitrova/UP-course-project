/**
*  
* Solution to course project # <09>
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Ivanina Dimitrova
* @idnumber <1MI0600686>
* @compiler VC
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

bool wordExists(const char word[]) {
    char w[10];
    ifstream file("words.txt");
    while (file >> w) {
        if (strEqual(w, word)) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void removeWord() {
    char word[10], w[10];
    cout << "Word to remove: ";
    cin >> word;

    ifstream in("words.txt");
    ofstream out("temp.txt");
    bool removed = false;

    while (in >> w) {
        if (!strEqual(w, word))
            out << w << endl;
        else
            removed = true;
    }

    in.close();
    out.close();

    remove("words.txt");
    rename("temp.txt", "words.txt");

    if (removed)
        cout << "Word removed.\n";
    else
        cout << "Word not found.\n";
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

    if (!validWord(word, strLen(word))) {
        cout << "Invalid word!\n";
        return;
    }

    if (wordExists(word)) {
        cout << "Word already exists!\n";
        return;
    }

    ofstream file("words.txt", ios::app);
    file << word << endl;
    file.close();

    cout << "Word added.\n";
}

void updateLeaderboard(const char user[], bool win) {
    char name[30];
    int games, wins;
    bool found = false;

    ifstream in("leaderboard.txt");
    ofstream out("temp.txt");

    while (in >> name >> games >> wins) {
        if (strEqual(name, user)) {
            games++;
            if (win) wins++;
            found = true;
        }
        out << name << " " << games << " " << wins << "\n";
    }

    if (!found)
        out << user << " 1 " << (win ? 1 : 0) << "\n";

    in.close();
    out.close();

    remove("leaderboard.txt");
    rename("temp.txt", "leaderboard.txt");
}

void showLeaderboard() {
    char name[30];
    int games, wins;

    ifstream file("leaderboard.txt");
    cout << "\n--- Leaderboard ---\n";
    while (file >> name >> games >> wins) {
        cout << name << " | Games: " << games
            << " | Wins: " << wins << "\n";
    }
    file.close();
}

void showLeaderboardSorted(bool byWinrate) {
    char name[100][30];
    int games[100], wins[100];
    int count = 0;

    ifstream file("leaderboard.txt");
    while (file >> name[count] >> games[count] >> wins[count])
        count++;
    file.close();

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            double a = byWinrate ? 
                (games[i] ? (double)wins[i] / games[i] : 0) : games[i];
            double b = byWinrate ? 
                (games[j] ? (double)wins[j] / games[j] : 0) : games[j];

            if (b > a) {
                swap(games[i], games[j]);
                swap(wins[i], wins[j]);

                char temp[30];
                strCopy(temp, name[i]);
                strCopy(name[i], name[j]);
                strCopy(name[j], temp);
            }
        }
    }

    cout << "\n--- Leaderboard ---\n";
    for (int i = 0; i < count; i++) {
        cout << name[i] << " | Games: " << games[i]
             << " | Wins: " << wins[i];
        if (games[i] > 0)
            cout << " | Winrate: " << (wins[i] * 100 / games[i]) << "%";
        cout << endl;
    }
}

void checkGuess(const char secret[], const char guess[]) {
    for (int i = 0; secret[i] != '\0'; i++) {
        if (guess[i] == secret[i])
            cout << GREEN << guess[i] << RESET;
        else if (containsChar(secret, guess[i]))
            cout << YELLOW << guess[i] << RESET;
        else
            cout << guess[i];
    }
    cout << "\n";
}

void playGame(const char user[]) {
    char secret[10], guess[10];
    int attempts = 6;

    getRandomWord(secret);
    int len = strLen(secret);

    cout << "\nGuess the word (" << len << " letters)\n";

    for (int i = 0; i < attempts; i++) {
        cout << "Attempt " << i + 1 << ": ";
        cin >> guess;

        if (!validWord(guess, len)) {
            cout << "Invalid word!\n";
            i--;
            continue;
        }

        checkGuess(secret, guess);

        if (strEqual(secret, guess)) {
            cout << "You WIN!\n";
            updateLeaderboard(user, true);
            return;
        }
    }

    cout << "You LOST! Word was: " << secret << "\n";
    updateLeaderboard(user, false);
}

void adminMenu(const char user[]) {
    int choice;
    do {
        cout << "\n1. Add word\n2. Remove word\n3. Leaderboard (games)\n4. Leaderboard (winrate)\n5. Logout\nChoice: ";
        cin >> choice;

        if (choice == 1) addWord();
        else if (choice == 2) removeWord();
        else if (choice == 3) showLeaderboardSorted(false);
        else if (choice == 4) showLeaderboardSorted(true);

    } while (choice != 5);
}

void userMenu(const char user[]) {
    int choice;
    do {
        cout << "\n1. Play\n2. Leaderboard (games)\n3. Leaderboard (winrate)\n4. Logout\nChoice: ";
        cin >> choice;

        if (choice == 1) playGame(user);
        else if (choice == 2) showLeaderboardSorted(false);
        else if (choice == 3) showLeaderboardSorted(true);

    } while (choice != 4);
}

int main() {
    srand(1234);

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