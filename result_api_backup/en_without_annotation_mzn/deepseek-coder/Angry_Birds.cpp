#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

int main() {
    int T;
    cin >> T;
    vector<int> n(T);
    for (int i = 0; i < T; ++i) {
        cin >> n[i];
    }

    int sum_n = accumulate(n.begin(), n.end(), 0);
    vector<float> x(sum_n), y(sum_n);
    for (int i = 0; i < sum_n; ++i) {
        cin >> x[i] >> y[i];
    }

    vector<int> split_n(T);
    for (int i = 1; i < T; ++i) {
        split_n[i] = split_n[i - 1] + n[i - 1];
    }

    int max_n = *max_element(n.begin(), n.end());

    vector<int> answer(T, 0);

    for (int t = 0; t < T; ++t) {
        vector<pair<float, float>> lines;
        for (int j = split_n[t]; j < split_n[t] + n[t]; ++j) {
            bool found = false;
            for (auto& line : lines) {
                if (abs(line.first * x[j] * x[j] + line.second * x[j] - y[j]) < 1e-6) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                lines.emplace_back(-10, y[j] / x[j]);
                ++answer[t];
            }
        }
    }

    for (int t = 0; t < T; ++t) {
        cout << answer[t] << " ";
    }
    cout << endl;

    return 0;
}
