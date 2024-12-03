#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Earthworm {
    long long length;
    int time;
    bool operator<(const Earthworm &other) const {
        return length < other.length;
    }
};

int main() {
    int n, m, q, u, v, t;
    cin >> n >> m >> q >> u >> v >> t;
    double p = static_cast<double>(u) / v;

    priority_queue<Earthworm> pq;
    vector<int> initial_lengths(n);
    for (int i = 0; i < n; ++i) {
        cin >> initial_lengths[i];
    }
    sort(initial_lengths.begin(), initial_lengths.end(), greater<int>());
    for (int i = 0; i < n; ++i) {
        pq.push({initial_lengths[i], 0});
    }

    vector<long long> cut_lengths;
    for (int i = 1; i <= m; ++i) {
        Earthworm longest = pq.top();
        pq.pop();
        long long current_length = longest.length + (i - longest.time - 1) * q;
        cut_lengths.push_back(current_length);
        long long cut_part1 = static_cast<long long>(p * current_length);
        long long cut_part2 = current_length - cut_part1;
        pq.push({cut_part1 - q * i, i});
        pq.push({cut_part2 - q * i, i});
    }

    vector<long long> final_lengths;
    while (!pq.empty()) {
        Earthworm e = pq.top();
        pq.pop();
        final_lengths.push_back(e.length + (m - e.time) * q);
    }

    for (int i = t - 1; i < m; i += t) {
        cout << cut_lengths[i] << " ";
    }
    cout << endl;

    for (int i = t - 1; i < final_lengths.size(); i += t) {
        cout << final_lengths[i] << " ";
    }
    cout << endl;

    return 0;
}
