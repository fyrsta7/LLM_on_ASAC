#include <iostream>
using namespace std;

int give(int day, int cur) {
    while(day > cur) {
        day -= cur;
        cur++;
    }
    return cur;
}

int main() {
    int n;
    cin >> n;
    int total = 0;
    for (int i = 1; i <= n; ++i) {
        total += give(i, 1);
    }
    cout << total << endl;
    return 0;
}