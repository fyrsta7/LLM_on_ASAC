#include <iostream>
#include <vector>
#include <unordered_set>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> numbers(n);
    std::unordered_set<int> numSet;

    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
        numSet.insert(numbers[i]);
    }

    int count = 0;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                int sum = numbers[i] + numbers[j];
                if (numSet.count(sum)) {
                    count++;
                }
            }
        }
    }

    // Each valid sum will be counted twice (a+b and b+a), so divide by 2
    count /= 2;

    std::cout << count << std::endl;

    return 0;
}