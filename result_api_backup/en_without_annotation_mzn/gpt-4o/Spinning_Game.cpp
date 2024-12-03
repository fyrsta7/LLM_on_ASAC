#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int n, m, k, x;
    cin >> n >> m >> k >> x;

    long long rounds = pow(10, k);
    long long final_state = x;

    for (int i = 0; i < rounds; ++i) {
        final_state = (final_state + m) % n;
    }

    cout << final_state << endl;
    return 0;
}