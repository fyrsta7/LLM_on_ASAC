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
    int result = 0;

    while (left <= right) {
        int mid = (left + right) / 2;
        int count = 0;
        int prev = 0;

        for (int i = 0; i < N; ++i) {
            if (D[i] - prev >= mid) {
                prev = D[i];
            } else {
                count++;
            }
        }

        if (count <= M) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    cout << "mindist=" << result << endl;
    return 0;
}