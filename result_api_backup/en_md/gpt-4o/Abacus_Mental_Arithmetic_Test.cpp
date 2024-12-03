#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    sort(numbers.begin(), numbers.end());
    int count = 0;

    for (int i = 2; i < n; ++i) {
        int target = numbers[i];
        int left = 0, right = i - 1;
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum == target) {
                count++;
                break;
            } else if (sum < target) {
                ++left;
            } else {
                --right;
            }
        }
    }

    cout << count << endl;
    return 0;
}