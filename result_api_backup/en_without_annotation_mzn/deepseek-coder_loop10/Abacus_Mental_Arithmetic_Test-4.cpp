#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> data(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> data[i];
    }

    std::unordered_set<int> unique_data(data.begin(), data.end());
    std::unordered_set<int> ans;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                int sum = data[i] + data[j];
                if (unique_data.find(sum) != unique_data.end()) {
                    ans.insert(sum);
                }
            }
        }
    }

    std::cout << ans.size() << std::endl;
    return 0;
}