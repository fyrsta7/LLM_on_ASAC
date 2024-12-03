#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Toy {
    int orientation;
    string profession;
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<Toy> toys(n);
    for (int i = 0; i < n; ++i) {
        cin >> toys[i].orientation >> toys[i].profession;
    }

    int current = 0;
    for (int i = 0; i < m; ++i) {
        int a, s;
        cin >> a >> s;
        if (a == 0) { // count to the left
            if (toys[current].orientation == 0) { // facing inside
                current = (current + s) % n;
            } else { // facing outside
                current = (current - s + n) % n;
            }
        } else { // count to the right
            if (toys[current].orientation == 0) { // facing inside
                current = (current - s + n) % n;
            } else { // facing outside
                current = (current + s) % n;
            }
        }
    }

    cout << toys[current].profession << endl;
    return 0;
}