#include <iostream>
using namespace std;

int hn_tower(int n) {
    if (n == 0) return 0;
    return 3 * hn_tower(n - 1) + 2;
}

int main() {
    int n;
    cin >> n;
    cout << hn_tower(n) << endl;
    return 0;
}