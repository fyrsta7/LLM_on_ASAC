#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> d(n);
    for (int i = 0; i < n; ++i) {
        cin >> d[i];
    }

    long long days = 0;
    while (true) {
        int start = -1;
        int minDepth = 10001;
        for (int i = 0; i < n; ++i) {
            if (d[i] > 0) {
                if (start == -1) {
                    start = i;
                }
                minDepth = min(minDepth, d[i]);
            } else if (start != -1) {
                for (int j = start; j < i; ++j) {
                    d[j] -= minDepth;
                }
                days += minDepth;
                start = -1;
                minDepth = 10001;
            }
        }
        if (start != -1) {
            for (int j = start; j < n; ++j) {
                d[j] -= minDepth;
            }
            days += minDepth;
        }
        if (all_of(d.begin(), d.end(), [](int depth) { return depth == 0; })) {
            break;
        }
    }

    cout << days << endl;
    return 0;
}
