#include <iostream>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>

int main() {
    int k, N;
    std::cin >> k >> N;

    std::set<int> sequence;
    int limit = 1 << k;  // The maximum number of distinct terms we can generate is 2^k - 1
    for (int i = 0; i < limit; ++i) {
        int sum = 0;
        for (int j = 0; j < k; ++j) {
            if (i & (1 << j)) {
                sum += std::pow(k, j);
            }
        }
        sequence.insert(sum);
    }

    std::vector<int> result(sequence.begin(), sequence.end());
    std::sort(result.begin(), result.end());

    std::cout << result[N - 1] << std::endl;
    return 0;
}