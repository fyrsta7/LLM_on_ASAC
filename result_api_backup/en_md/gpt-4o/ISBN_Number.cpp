#include <iostream>
#include <string>
using namespace std;

int charToInt(char c) {
    return c - '0';
}

int main() {
    string isbn;
    cin >> isbn;

    int sum = 0, count = 1;
    for (char c : isbn) {
        if (c != '-') {
            if (c == 'X') {
                sum += 10 * count;
            } else {
                sum += charToInt(c) * count;
            }
            count++;
        }
    }

    int correctIdentifier = sum % 11;
    char correctIdentifierChar = (correctIdentifier == 10) ? 'X' : char('0' + correctIdentifier);

    if (isbn.back() == correctIdentifierChar) {
        cout << "Right" << endl;
    } else {
        isbn.back() = correctIdentifierChar;
        cout << isbn << endl;
    }

    return 0;
}