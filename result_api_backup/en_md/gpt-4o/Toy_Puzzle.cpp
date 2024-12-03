
```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Toy {
    int orientation; // 0 for inside, 1 for outside
    string profession;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<Toy> toys(n);
    for (int i = 0; i < n; ++i) {
        cin >> toys[i].orientation >> toys[i].profession;
    }

    int current_pos = 0;
    for (int i = 0; i < m; ++i) {
        int a, s;
        cin >> a >> s;

        if (a == 0) { // count to the left
            if (toys[current_pos].orientation == 0) { // facing inside
                current_pos = (current_pos + s) % n;
            } else { // facing outside
                current_pos = (current_pos - s + n) % n;
            }
        } else { // count to the right
            if (toys[current_pos].orientation == 0) { // facing inside
                current_pos = (current_pos - s + n) % n;
            } else { // facing outside
                current_pos = (current_pos + s) % n;
            }
        }
    }

    cout << toys[current_pos].profession << endl;

    return 0;
}
