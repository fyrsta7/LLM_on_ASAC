#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Toy {
    int direction; // 0 for inside, 1 for outside
    string profession;
};

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<Toy> toys(n);
    for (int i = 0; i < n; ++i) {
        cin >> toys[i].direction >> toys[i].profession;
    }
    
    int currentPosition = 0; // Start from the first toy
    for (int i = 0; i < m; ++i) {
        int a, s;
        cin >> a >> s;
        if (toys[currentPosition].direction == 0) { // facing inside
            if (a == 0) { // left
                currentPosition = (currentPosition + s) % n;
            } else { // right
                currentPosition = (currentPosition - s + n) % n;
            }
        } else { // facing outside
            if (a == 0) { // left
                currentPosition = (currentPosition - s + n) % n;
            } else { // right
                currentPosition = (currentPosition + s) % n;
            }
        }
    }
    
    cout << toys[currentPosition].profession << endl;
    return 0;
}