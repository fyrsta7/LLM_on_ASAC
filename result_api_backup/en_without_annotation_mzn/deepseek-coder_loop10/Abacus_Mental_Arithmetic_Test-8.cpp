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

    std::unordered_set<int> seen;
    std::unordered_set<int> ans;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                int sum = data[i] + data[j];
                if (seen.find(sum) != seen.end()) {
                    ans.insert(sum);
                }
            }
        }
        seen.insert(data[i]);
    }

    std::cout << ans.size() << std::endl;
    return 0;
}