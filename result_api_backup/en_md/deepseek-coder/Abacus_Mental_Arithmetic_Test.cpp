#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    
    int count = 0;
    for (int i = 2; i < n; ++i) {
        int left = 0, right = i - 1;
        while (left < right) {
            if (nums[left] + nums[right] == nums[i]) {
                ++count;
                break;
            } else if (nums[left] + nums[right] < nums[i]) {
                ++left;
            } else {
                --right;
            }
        }
    }
    cout << count << endl;
    return 0;
}