#include <iostream>
using namespace std;

int main() {
    int n, i, j;
    cin >> n >> i >> j;

    int layer = min(min(i-1, j-1), min(n-i, n-j));
    int side_length = n-2*layer;
    int count_prev_layers = (n - 2*layer)*(n - 2*layer) - side_length * side_length;

    if (i-1 == layer) {
        cout << count_prev_layers + (j - layer) + 1 << endl;
    } else if (j == n-layer) {
        cout << count_prev_layers + side_length + (i-layer-1) << endl;
    } else if (i == n-layer) {
        cout << count_prev_layers + 3*side_length - 2 - (j-layer-1) << endl;
    } else {
        cout << count_prev_layers + 4*side_length - 4 - (i-layer-1) << endl;
    }

    return 0;
}