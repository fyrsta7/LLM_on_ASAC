#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

int main() {
    int N;
    std::cin >> N;
    std::set<int> unique_numbers; // Using set to automatically handle duplicates

    for (int i = 0; i < N; ++i) {
        int num;
        std::cin >> num;
        unique_numbers.insert(num); // Insert into set
    }

    std::vector<int> sorted_numbers(unique_numbers.begin(), unique_numbers.end()); // Copy to vector
    std::sort(sorted_numbers.begin(), sorted_numbers.end()); // Sort the numbers (not strictly necessary since set is ordered)

    std::cout << sorted_numbers.size() << std::endl; // Output the count of unique numbers
    for (int number : sorted_numbers) {
        std::cout << number << " "; // Output the sorted unique numbers
    }
    std::cout << std::endl; // Final newline for formatting

    return 0;
}