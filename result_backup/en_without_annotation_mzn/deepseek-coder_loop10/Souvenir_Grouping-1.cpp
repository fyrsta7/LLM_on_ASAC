#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int w, n;
    cin >> w >> n;
    vector<int> P(n);
    for (int i = 0; i < n; ++i) {
        cin >> P[i];
    }

    sort(P.begin(), P.end(), greater<int>());

    vector<int> weight(n, 0);
    vector<int> num(n, 0);
    int object = 0;

    for (int i = 0; i < n; ++i) {
        bool placed = false;
        for (int j = 0; j < object; ++j) {
            if (num[j] < 2 && weight[j] + P[i] <= w) {
                weight[j] += P[i];
                num[j]++;
                placed = true;
                break;
            }
        }
        if (!placed) {
            weight[object] = P[i];
            num[object] = 1;
            object++;
        }
    }

    cout << object << endl;
    return 0;
}