#include <iostream>
using namespace std;

int main() {
    int n, m, k, x;
    cin >> n >> m >> k >> x;

    long long rounds = 1;
    for (int i = 0; i < k; ++i) {
        rounds *= 10;
    }

    int final_position = (x + rounds * m) % n;
    cout << final_position << endl;

    return 0;
}