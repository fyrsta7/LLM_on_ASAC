#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    long long a, b;
    cin >> a >> b;

    // Calculate the value of the most expensive item that cannot be paid
    long long N = a * b - a - b;

    cout << N << endl;

    return 0;
}