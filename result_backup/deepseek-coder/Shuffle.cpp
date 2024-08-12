#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> t(n);
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }
    sort(t.begin(), t.end());

    long long total_waiting_time = 0;
    long long current_time = 0;
    for (int i = 0; i < n; ++i) {
        if (t[i] > current_time) {
            current_time = t[i];
        }
        total_waiting_time += current_time - t[i];
        current_time += m;
    }

    cout << total_waiting_time << endl;
    return 0;
}
