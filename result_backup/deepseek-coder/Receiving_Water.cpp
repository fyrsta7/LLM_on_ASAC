#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> w(n);
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }

    vector<int> faucets(m, 0);
    vector<int> students(m, 0);

    for (int i = 0; i < min(n, m); ++i) {
        faucets[i] = w[i];
        students[i] = i;
    }

    int time = 0;
    while (true) {
        int min_time = *min_element(faucets.begin(), faucets.end());
        time += min_time;

        for (int i = 0; i < m; ++i) {
            if (faucets[i] > 0) {
                faucets[i] -= min_time;
                if (faucets[i] == 0) {
                    int next_student = students[i] + m;
                    if (next_student < n) {
                        faucets[i] = w[next_student];
                        students[i] = next_student;
                    }
                }
            }
        }

        if (all_of(faucets.begin(), faucets.end(), [](int x) { return x == 0; })) {
            break;
        }
    }

    cout << time << endl;
    return 0;
}
