#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool canAchieveMinJump(const vector<int>& rocks, int L, int minJump, int M) {
    int lastRock = 0, removedRocks = 0;
    for (int i = 0; i < rocks.size(); ++i) {
        if (rocks[i] - lastRock < minJump) {
            removedRocks++;
        } else {
            lastRock = rocks[i];
        }
        
        if (removedRocks > M) {
            return false;
        }
    }

    return (L - lastRock) >= minJump || removedRocks <= M;
}

int maximizeShortestJump(int L, const vector<int>& rocks, int N, int M) {
    int left = 1, right = L, best = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (canAchieveMinJump(rocks, L, mid, M)) {
            best = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return best;
}

int main() {
    int L, N, M;
    cin >> L >> N >> M;

    vector<int> rocks(N);
    for (int i = 0; i < N; ++i) {
        cin >> rocks[i];
    }

    cout << maximizeShortestJump(L, rocks, N, M) << endl;

    return 0;
}