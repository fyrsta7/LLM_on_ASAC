#include <iostream>
#include <queue>
#include <vector>

int main() {
    int n, m, q, u, v, t;
    std::cin >> n >> m >> q >> u >> v >> t;

    double p = (double)u / v;
    std::priority_queue<int> pq;
    for (int i = 0; i < n; ++i) {
        int length;
        std::cin >> length;
        pq.push(length);
    }

    std::vector<int> cut_lengths;
    std::vector<int> every_tth_second;

    for (int i = 1; i <= m; ++i) {
        int max_length = pq.top();
        pq.pop();
        cut_lengths.push_back(max_length);
        int left = (int)(p * max_length);
        int right = max_length - left;

        pq.push(left + q);
        pq.push(right + q);

        if (i % t == 0) {
            every_tth_second.push_back(max_length);
        }
    }

    for (int length : every_tth_second) {
        std::cout << length << " ";
    }
    std::cout << "\n";

    std::vector<int> final_lengths;
    while (!pq.empty()) {
        final_lengths.push_back(pq.top());
        pq.pop();
    }

    for (int i = 0; i < final_lengths.size(); ++i) {
        std::cout << final_lengths[i];
        if (i % t == t - 1 || i == final_lengths.size() - 1) {
            std::cout << "\n";
        } else {
            std::cout << " ";
        }
    }

    return 0;
}