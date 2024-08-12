#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(int year, int month, int day) {
    if (month < 1 || month > 12 || day < 1) return false;
    int daysInMonth = 31;
    switch (month) {
        case 2:
            daysInMonth = isLeapYear(year) ? 29 : 28;
            break;
        case 4: case 6: case 9: case 11:
            daysInMonth = 30;
            break;
    }
    return day <= daysInMonth;
}

bool isPalindrome(const std::string& date) {
    return date == std::string(date.rbegin(), date.rend());
}

int countPalindromeDates(const std::string& startDate, const std::string& endDate) {
    int count = 0;
    
    std::stringstream ssStart(startDate);
    std::stringstream ssEnd(endDate);
    
    int startYear, startMonth, startDay;
    int endYear, endMonth, endDay;
    
    ssStart >> startYear >> std::setw(2) >> startMonth >> std::setw(2) >> startDay;
    ssEnd >> endYear >> std::setw(2) >> endMonth >> std::setw(2) >> endDay;
    
    while (true) {
        std::string dateStr = std::to_string(startYear) + 
                               std::setw(2) + std::setfill('0') + std::to_string(startMonth) +
                               std::setw(2) + std::setfill('0') + std::to_string(startDay);
        
        if (isPalindrome(dateStr)) {
            count++;
        }
        
        // Increment the date
        startDay++;
        if (!isValidDate(startYear, startMonth, startDay)) {
            startDay = 1;
            startMonth++;
            if (startMonth > 12) {
                startMonth = 1;
                startYear++;
            }
        }
        
        // Check if we've reached the end date
        if (startYear > endYear || (startYear == endYear && (startMonth > endMonth || (startMonth == endMonth && startDay > endDay)))) {
            break;
        }
    }
    
    return count;
}

int main() {
    std::string date1, date2;
    std::cin >> date1 >> date2;
    std::cout << countPalindromeDates(date1, date2) << std::endl;
    return 0;
}