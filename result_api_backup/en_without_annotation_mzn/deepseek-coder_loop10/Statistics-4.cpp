#include <iostream>
#include <vector>

using namespace std;

int count_two(int x) {
    int count = 0;
    while (x > 0) {
        if (x % 10 == 2) count++;
        x /= 10;
    }
    return count;
}

int main() {
    int l, r;
    cin >> l >> r;

    int answer = 0;
    for (int i = l; i <= r; ++i) {
        answer += count_two(i);
    }

    cout << answer << endl;
    return 0;
}