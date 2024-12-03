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

    vector<vector<int>> bird(sum_n);
    vector<float> a(sum_n), b(sum_n);
    vector<int> answer(T);

    for (int t = 0; t < T; ++t) {
        for (int j = split_n[t]; j < split_n[t] + n[t]; ++j) {
            float min_a = -10, max_a = 0;
            float min_b = -10, max_b = 10;
            bool valid = true;
            for (int k = 0; k < sum_n; ++k) {
                if (k != j) {
                    float det = x[j] * x[j] * (y[k] - y[j]) - x[k] * x[k] * (y[j] - y[k]);
                    float denom = x[j] * x[j] - x[k] * x[k];
                    if (denom == 0) continue;
                    float a_k = det / denom;
                    float b_k = (y[j] - a_k * x[j] * x[j]) / x[j];
                    if (a_k < min_a || a_k > max_a || b_k < min_b || b_k > max_b) {
                        valid = false;
                        break;
                    }
                    min_a = max(min_a, a_k);
                    max_a = min(max_a, a_k);
                    min_b = max(min_b, b_k);
                    max_b = min(max_b, b_k);
                }
            }
            if (valid) {
                a[j] = min_a;
                b[j] = min_b;
                answer[t]++;
            }
        }
    }

    for (int t = 0; t < T; ++t) {
        cout << answer[t] << " ";
    }
    cout << endl;

    return 0;
}
