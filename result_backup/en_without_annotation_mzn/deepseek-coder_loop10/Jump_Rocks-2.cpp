#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int main() {
    int L, N, M;
    cin >> L >> N >> M;
    vector<int> D(N);
    for (int i = 0; i < N; ++i) {
        cin >> D[i];
    }

    sort(D.begin(), D.end());

    int left = 0, right = L;
    while (left < right) {
        int mid = (left + right + 1) / 2;
        int count = 0;
        int last = 0;
        for (int i = 0; i < N; ++i) {
            if (D[i] - last < mid) {
                count++;
            } else {
                last = D[i];
            }
        }
        if (L - last < mid) {
            count++;
        }
        if (count <= M) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    cout << "mindist=" << left << endl;
    return 0;
}
