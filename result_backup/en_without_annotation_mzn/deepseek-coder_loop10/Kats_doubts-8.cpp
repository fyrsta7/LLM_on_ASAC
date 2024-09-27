#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int a, b;
    cin >> a >> b;

    int max_ans = 2000;
    int g = gcd(a, b);
    int max_val = (a / g) * (b / g) * g - g;

    int ans = min(max_ans, max_val);
    cout << ans << endl;

    return 0;
}