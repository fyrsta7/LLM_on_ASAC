#include <iostream>
using namespace std;

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(int year, int month, int day) {
    if (month < 1 || month > 12 || day < 1) return false;
    if (month == 2) return isLeapYear(year) ? day <= 29 : day <= 28;
    if (month == 4 || month == 6 || month == 9 || month == 11) return day <= 30;
    return day <= 31;
}

bool isPalindrome(int date) {
    string s = to_string(date);
    while (s.length() < 8) s = "0" + s;
    for (int i = 0; i < 4; ++i) {
        if (s[i] != s[7 - i]) return false;
    }
    return true;
}

int convertToDateInt(int year, int month, int day) {
    return year * 10000 + month * 100 + day;
}

int main() {
    int startDate, endDate;
    cin >> startDate >> endDate;

    int startYear = startDate / 10000;
    int startMonth = (startDate / 100) % 100;
    int startDay = startDate % 100;
    
    int endYear = endDate / 10000;
    int endMonth = (endDate / 100) % 100;
    int endDay = endDate % 100;
    
    int count = 0;

    for (int year = startYear; year <= endYear; ++year) {
        int monthStart = year == startYear ? startMonth : 1;
        int monthEnd = year == endYear ? endMonth : 12;
        
        for (int month = monthStart; month <= monthEnd; ++month) {
            int dayStart = (year == startYear && month == startMonth) ? startDay : 1;
            int dayEnd = (year == endYear && month == endMonth) ? endDay : (month == 2 ? (isLeapYear(year) ? 29 : 28) : (month == 4 || month == 6 || month == 9 || month == 11 ? 30 : 31));

            for (int day = dayStart; day <= dayEnd; ++day) {
                if (isValidDate(year, month, day)) {
                    int dateInt = convertToDateInt(year, month, day);
                    if (isPalindrome(dateInt)) {
                        ++count;
                    }
                }
            }
        }
    }

    cout << count << endl;

    return 0;
}