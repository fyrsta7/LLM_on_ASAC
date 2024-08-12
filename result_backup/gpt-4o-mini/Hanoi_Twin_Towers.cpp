#include <iostream>
using namespace std;

int hanoiTwinTowers(int n) {
    if (n == 1) return 2; // Base case for n=1
    return 2 * hanoiTwinTowers(n - 1) + 2; // Recursive case
}

int main() {
    int n;
    cin >> n;
    cout << hanoiTwinTowers(n) << endl;
    return 0;
}