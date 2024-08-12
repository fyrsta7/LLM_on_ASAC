#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> targets(n + 1);
    vector<int> in_degree(n + 1, 0);
    vector<int> rounds(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        cin >> targets[i];
        ++in_degree[targets[i]];
    }

    vector<int> queue;
    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) {
            queue.push_back(i);
        }
    }

    while (!queue.empty()) {
        int student = queue.back();
        queue.pop_back();
        int target = targets[student];
        rounds[target] = max(rounds[target], rounds[student] + 1);
        if (--in_degree[target] == 0) {
            queue.push_back(target);
        }
    }

    int max_rounds = 0;
    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] > 0) {
            int cycle_length = 0;
            int current = i;
            do {
                current = targets[current];
                ++cycle_length;
            } while (current != i);
            max_rounds = max(max_rounds, cycle_length + rounds[i]);
        }
    }

    cout << max_rounds << endl;
    return 0;
}
