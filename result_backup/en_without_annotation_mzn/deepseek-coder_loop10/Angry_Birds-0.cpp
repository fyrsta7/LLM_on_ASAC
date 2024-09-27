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
    vector<int> answer(T, 0);

    for (int t = 0; t < T; ++t) {
        for (int j = split_n[t]; j < split_n[t] + n[t]; ++j) {
            bool found = false;
            for (int k = 0; k < sum_n; ++k) {
                if (k != j && x[k] != x[j]) {
                    a[j] = (y[k] - y[j]) / (x[k] * x[k] - x[j] * x[j]);
                    b[j] = y[j] - a[j] * x[j] * x[j];
                    if (a[j] < 0 && a[j] >= -10 && b[j] <= 10 && b[j] >= -10) {
                        bool valid = true;
                        for (int l = 0; l < sum_n; ++l) {
                            if (l != j && l != k && a[j] * x[l] * x[l] + b[j] * x[l] == y[l]) {
                                valid = false;
                                break;
                            }
                        }
                        if (valid) {
                            bird[j].push_back(k);
                            found = true;
                        }
                    }
                }
            }
            if (found) {
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
