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

int main() {
	while (true) {
    cout << "\n--- WORDLE ---\n";
    cout << "1. Login\n";
    cout << "2. Sign in\n";
    cout << "3. Exit\nChoice: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        login();
    }
    else if (choice == 2) {
        registerUser();
    }
    else {
        break;
    }
}

return 0;
}