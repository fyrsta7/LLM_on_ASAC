#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> heights(n);
    for (int i = 0; i < n; ++i) {
        cin >> heights[i];
    }

    int operations = 0;
    int current_height = 0;
    for (int i = 0; i < n; ++i) {
        if (heights[i] > current_height) {
            operations += heights[i] - current_height;
            current_height = heights[i];
        } else if (heights[i] < current_height) {
            current_height = heights[i];
        }
    }

    cout << operations << endl;
    return 0;
}
