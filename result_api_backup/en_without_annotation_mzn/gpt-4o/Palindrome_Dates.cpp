#include <iostream>
using namespace std;

bool isLeapYear(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

bool isValidDate(int y, int m, int d) {
    if (m < 1 || m > 12 || d < 1) return false;
    int daysInMonth[] = {31, isLeapYear(y) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return d <= daysInMonth[m - 1];
}

bool isPalindromic(int w) {
    int rev = 0, num = w;
    while (num > 0) {
        rev = rev * 10 + num % 10;
        num /= 10;
    }
    return w == rev;
}

bool isValidPalindromicDate(int date) {
    int y = date / 10000;
    int m = (date / 100) % 100;
    int d = date % 100;
    return isValidDate(y, m, d) && isPalindromic(date);
}

int countValidPalindromicDates(int s, int t) {
    int count = 0;
    for (int date = s; date <= t; ++date) {
        if (isValidPalindromicDate(date)) {
            count++;
        }
    }
    return count;
}

int main() {
    int s, t;
    cin >> s >> t;
    int res = countValidPalindromicDates(s, t);
    cout << "res=" << res << endl;
    return 0;
}