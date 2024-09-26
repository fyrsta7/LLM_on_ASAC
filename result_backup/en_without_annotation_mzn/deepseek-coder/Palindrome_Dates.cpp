#include <iostream>
#include <vector>

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
    int original = num;
    int reversed = 0;
    while (num > 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    return original == reversed;
}

int countPalindromeDates(int s, int t) {
    int count = 0;
    for (int date = s; date <= t; ++date) {
        int year = date / 10000;
        int month = (date / 100) % 100;
        int day = date % 100;
        if (isValidDate(year, month, day) && isPalindrome(date)) {
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