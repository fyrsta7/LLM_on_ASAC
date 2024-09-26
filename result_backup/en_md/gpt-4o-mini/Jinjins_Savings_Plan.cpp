#include <iostream>
#include <vector>

int main() {
    std::vector<int> budgets(12);
    for (int i = 0; i < 12; ++i) {
        std::cin >> budgets[i];
    }

    int savings = 0;
    int totalSavings = 0;
    const int monthlyPocketMoney = 300;
    
    for (int month = 0; month < 12; ++month) {
        int currentMoney = savings + monthlyPocketMoney;
        
        if (currentMoney < budgets[month]) {
            std::cout << -(month + 1) << std::endl;
            return 0;
        }
        
        int surplus = currentMoney - budgets[month];
        int deposit = (surplus / 100) * 100; // Maximum positive integer multiple of 100
        if (deposit > 0) {
            savings += deposit * 1.2; // Add 20% return to the savings
        }
        savings += currentMoney - deposit - budgets[month];
    }

    std::cout << static_cast<int>(savings) << std::endl;
    return 0;
}