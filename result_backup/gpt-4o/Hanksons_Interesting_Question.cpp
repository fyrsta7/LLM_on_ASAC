#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
    while (b != 0) {
        ll temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

ll lcm(ll a, ll b) {
    return (a / gcd(a, b)) * b;
}

int main() {
    int n;
    cin >> n;

    while (n--) {
        ll a0, a1, b0, b1;
        cin >> a0 >> a1 >> b0 >> b1;

        // Conditions must be met
        if (a0 % a1 != 0 || b1 % b0 != 0) {
            cout << 0 << endl;
            continue;
        }

        ll count = 0;
        ll l = (a0 / a1);
        ll g = b1 / b0;

        for (ll i = 1; i * i <= g; ++i) {
            if (g % i == 0) {
                if (gcd(i, l) == 1) {
                    count++;
                }
                if (i != g / i && gcd(g / i, l) == 1) {
                    count++;
                }
            }
        }

        cout << count << endl;
    }

    return 0;
}