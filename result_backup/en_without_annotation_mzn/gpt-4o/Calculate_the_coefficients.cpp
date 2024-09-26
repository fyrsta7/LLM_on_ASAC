#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int factorial(int num) {
    if (num == 0)
        return 1;
    int result = 1;
    for (int i = 1; i <= num; ++i)
        result = (result * i) % 10007;
    return result;
}

int combinatorial(int n, int k) {
    if (k > n) return 0;
    return (factorial(n) / (factorial(k) * factorial(n - k))) % 10007;
}

int main() {
    int a, b, k, n, m;
    cin >> a >> b >> k >> n >> m;

    int coefficient = combinatorial(k, n) * pow(a, n) * pow(b, m);
    coefficient = coefficient % 10007;

    cout << coefficient << endl;
    return 0;
}