#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

const int MOD = 998244353;

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> a(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> a[i][j];
        }
    }

    // Count the total number of dishes possible
    std::vector<int> total_count(n);
    for (int i = 0; i < n; ++i) {
        total_count[i] = std::accumulate(a[i].begin(), a[i].end(), 0);
    }

    // Step 1: Calculate all possible combinations of dishes
    long long total_schemes = 0;
    for (int k = 1; k <= n; ++k) { // k is the total number of dishes
        long long current_schemes = 0;

        // Generate all possible selections of k cooking methods
        std::vector<int> method_indices(n);
        std::iota(method_indices.begin(), method_indices.end(), 0);

        do {
            // Select first k methods
            long long selection_schemes = 1;
            for (int i = 0; i < k; ++i) {
                int method = method_indices[i];
                selection_schemes = selection_schemes * total_count[method] % MOD;
            }

            // Count ways to choose ingredients without exceeding limits
            // For selected k methods, calculate ingredient selection limits
            std::vector<int> ingredient_count(m, 0);
            for (int i = 0; i < k; ++i) {
                int method = method_indices[i];
                for (int j = 0; j < m; ++j) {
                    ingredient_count[j] += a[method][j];
                }
            }

            // Check for feasibility
            bool valid = true;
            for (int count : ingredient_count) {
                if (count > k / 2) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                current_schemes = (current_schemes + selection_schemes) % MOD;
            }

        } while (std::next_permutation(method_indices.begin(), method_indices.begin() + k));

        total_schemes = (total_schemes + current_schemes) % MOD;
    }

    std::cout << total_schemes << std::endl;
    return 0;
}