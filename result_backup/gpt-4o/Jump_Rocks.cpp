#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool canRemoveRocks(const vector<int>& rocks, int minDist, int L, int M) {
    int last = 0; 
    int removeCount = 0;
    for (int i = 1; i < rocks.size(); ++i) {
        if (rocks[i] - rocks[last] < minDist) {
            ++removeCount;
            if (removeCount > M) return false;
        } else {
            last = i;
        }
    }
    return (L - rocks[last] >= minDist);
}

int main() {
    int L, N, M;
    cin >> L >> N >> M;
    vector<int> rocks(N + 2);
    rocks[0] = 0; 
    for (int i = 1; i <= N; ++i) {
        cin >> rocks[i];
    }
    rocks[N + 1] = L;
    sort(rocks.begin(), rocks.end());
    
    int low = 0, high = L, result = 0;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (canRemoveRocks(rocks, mid, L, M)) {
            result = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    cout << result << endl;

    return 0;
}