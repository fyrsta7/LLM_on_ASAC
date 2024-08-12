#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void nextPermutation(vector<int>& nums) {
    int n = nums.size();
    int i = n - 2;
    while (i >= 0 && nums[i] >= nums[i + 1]) {
        i--;
    }
    if (i >= 0) {
        int j = n - 1;
        while (j >= 0 && nums[j] <= nums[i]) {
            j--;
        }
        swap(nums[i], nums[j]);
    }
    reverse(nums.begin() + i + 1, nums.end());
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> fingers(N);
    for (int i = 0; i < N; ++i) {
        cin >> fingers[i];
    }

    for (int i = 0; i < M; ++i) {
        nextPermutation(fingers);
    }

    for (int i = 0; i < N; ++i) {
        if (i > 0) cout << " ";
        cout << fingers[i];
    }
    cout << endl;

    return 0;
}
