#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minimum_students_to_step_out(int n, vector<int>& heights) {
    vector<int> left(n, 1), right(n, 1);
    
    // Calculate increasing subsequence lengths ending at each position
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (heights[i] > heights[j]) {
                left[i] = max(left[i], left[j] + 1);
            }
        }
    }

    // Calculate decreasing subsequence lengths starting at each position
    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (heights[i] > heights[j]) {
                right[i] = max(right[i], right[j] + 1);
            }
        }
    }

    // Calculate the maximum number of students in a valid chorus formation
    int max_length = 0;
    for (int i = 0; i < n; i++) {
        if (left[i] > 1 && right[i] > 1) {
            max_length = max(max_length, left[i] + right[i] - 1);
        }
    }

    // Minimum number of students to step out
    return n - max_length;
}

int main() {
    int n;
    cin >> n;
    vector<int> heights(n);

    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }

    cout << minimum_students_to_step_out(n, heights) << endl;

    return 0;
}