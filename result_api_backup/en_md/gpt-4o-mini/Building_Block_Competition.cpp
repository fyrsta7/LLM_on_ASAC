#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> heights(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> heights[i];
    }

    int operations = 0;
    for (int i = 1; i < n; ++i) {
        if (heights[i] > heights[i - 1]) {
            operations += heights[i] - heights[i - 1];
        }
    }
    operations += heights[0]; // Add initial height operations for the first block

    cout << operations << endl;
    return 0;
}