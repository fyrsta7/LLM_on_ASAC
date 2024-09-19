#include <iostream>
using namespace std;

int main() {
    int n, i, j;
    cin >> n >> i >> j;

    int layer = min(min(i - 1, n - i), min(j - 1, n - j));
    int start = layer * layer * 4 + 1;
    int size = n - layer * 2;

    int result;
    if (i - layer == 1) {
        result = start + (j - layer - 1);
    } else if (j - layer == size) {
        result = start + size - 1 + (i - layer - 1);
    } else if (i - layer == size) {
        result = start + 2 * (size - 1) + (size - j + layer - 1);
    } else {
        result = start + 3 * (size - 1) + (size - i + layer - 1);
    }

    cout << result << endl;
    return 0;
}