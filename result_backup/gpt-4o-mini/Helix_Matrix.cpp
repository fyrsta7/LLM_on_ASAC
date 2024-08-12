#include <iostream>
using namespace std;

int main() {
    int n, i, j;
    cin >> n >> i >> j;

    int layer = min(min(i-1, j-1), min(n-i, n-j));
    int size = n - 2 * layer;
    int startNum = layer * layer * 4 + 1;

    if (size == 1) {
        cout << startNum << endl;
        return 0;
    }

    int rightEnd = startNum + size - 1;
    int downEnd = rightEnd + size - 1;
    int leftEnd = downEnd + size - 1;

    if (i == layer + 1) {
        cout << startNum + (j - layer - 1) << endl;
    } else if (j == n - layer) {
        cout << rightEnd + (i - layer - 1) << endl;
    } else if (i == n - layer) {
        cout << downEnd - (j - layer - 1) << endl;
    } else {
        cout << leftEnd - (n - layer - i) << endl;
    }

    return 0;
}