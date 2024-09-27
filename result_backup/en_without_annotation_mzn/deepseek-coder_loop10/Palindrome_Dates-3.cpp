#include <iostream>
#include <string>
using namespace std;

bool isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

bool isValidDate(int year, int month, int day) {
    if (month < 1 || month > 12 || day < 1) return false;
    if (month == 2) {
        if (isLeapYear(year)) return day <= 29;
        return day <= 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) return day <= 30;
    return day <= 31;
}

bool isPalindrome(int num) {
    string s = to_string(num);
    int len = s.length();
    for (int i = 0; i < len / 2; ++i) {
        if (s[i] != s[len - 1 - i]) return false;
    }
    return true;
}

bool isValidPalindromeDate(int date) {
    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;
    return isValidDate(year, month, day) && isPalindrome(date);
}

int countPalindromeDates(int s, int t) {
    int count = 0;
    for (int i = s; i <= t; ++i) {
        if (isValidPalindromeDate(i)) {
            count++;
        }
    }
    return count;
}

int main() {
    int s, t;
    cin >> s >> t;
    cout << "res=" << countPalindromeDates(s, t) << endl;
    return 0;
}
