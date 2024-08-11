#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> depths(n);
    for (int i = 0; i < n; i++) {
        cin >> depths[i];
    }

    int days = 0;
    vector<int> prefixSum(n + 1, 0);

    for (int i = 0; i < n; i++) {
        prefixSum[i + 1] = prefixSum[i] + depths[i];
    }

    for (int i = 0; i < n; i++) {
        int remainingDepth = prefixSum[n] - prefixSum[i + 1];
        days += remainingDepth - depths[i];
    }

    cout << days << endl;

    return 0;
}