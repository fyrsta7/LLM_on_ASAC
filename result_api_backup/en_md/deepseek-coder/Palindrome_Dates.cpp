#include <iostream>
#include <string>
using namespace std;

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(int year, int month, int day) {
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if (month == 2) {
        if (isLeapYear(year)) return day <= 29;
        else return day <= 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) return day <= 30;
    return true;
}

bool isPalindrome(const string& date) {
    for (int i = 0; i < 4; ++i) {
        if (date[i] != date[7 - i]) return false;
    }
    return true;
}

int countPalindromeDates(const string& start, const string& end) {
    int count = 0;
    int startYear = stoi(start.substr(0, 4));
    int endYear = stoi(end.substr(0, 4));

    for (int year = startYear; year <= endYear; ++year) {
        string yearStr = to_string(year);
        string palindromeDate = yearStr;
        palindromeDate += yearStr[3];
        palindromeDate += yearStr[2];
        palindromeDate += yearStr[1];
        palindromeDate += yearStr[0];

        if (palindromeDate >= start && palindromeDate <= end) {
            int month = stoi(palindromeDate.substr(4, 2));
            int day = stoi(palindromeDate.substr(6, 2));
            if (isValidDate(year, month, day)) {
                ++count;
            }
        }
    }
    return count;
}

int main() {
    string start, end;
    cin >> start >> end;
    cout << countPalindromeDates(start, end) << endl;
    return 0;
}
