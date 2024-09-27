#include <iostream>
#include <string>

bool isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

bool isValidDate(int year, int month, int day) {
    if (month < 1 || month > 12 || day < 1) return false;
    if (month == 2) {
        if (isLeapYear(year)) return day <= 29;
        else return day <= 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) return day <= 30;
    return day <= 31;
}

bool isPalindrome(int num) {
    std::string s = std::to_string(num);
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
    for (int date = s; date <= t; ++date) {
        if (isValidPalindromeDate(date)) {
            ++count;
        }
    }
    return count;
}

int main() {
    int s, t;
    std::cin >> s >> t;
    int res = countPalindromeDates(s, t);
    std::cout << "res=" << res << std::endl;
    return 0;
}