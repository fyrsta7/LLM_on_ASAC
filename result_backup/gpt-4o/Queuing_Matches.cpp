#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 100000000 - 3;

int minSwaps(vector<int>& arr1, vector<int>& arr2, int n) {
    vector<pair<int, int>> v1(n), v2(n);
    for (int i = 0; i < n; ++i) {
        v1[i] = {arr1[i], i};
        v2[i] = {arr2[i], i};
    }

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    
    vector<bool> visited(n, false);
    vector<int> position(n);

    for (int i = 0; i < n; ++i) {
        position[v1[i].second] = v2[i].second;
    }

    int swaps = 0;
    for (int i = 0; i < n; ++i) {
        if (visited[i] || position[i] == i) continue;
        int cycle_size = 0;
        int j = i;
        while (!visited[j]) {
            visited[j] = true;
            j = position[j];
            ++cycle_size;
        }
        if (cycle_size > 0) {
            swaps += cycle_size - 1;
        }
    }
    return swaps % MOD;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr1(n), arr2(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr1[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> arr2[i];
    }

    cout << minSwaps(arr1, arr2, n) << endl;
    return 0;
}