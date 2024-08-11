#include <iostream>
using namespace std;

int main() {
    int n, m, k, x;
    cin >> n >> m >> k >> x;

    for (int i = 0; i < k; i++) {
        x = (x + m) % n;
    }

    cout << x << endl;

    return 0;
}