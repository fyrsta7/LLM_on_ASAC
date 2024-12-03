#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int n;
string addend1, addend2, sum;
vector<int> mapping(26, -1);
vector<bool> used;

bool isValid() {
    int carry = 0;
    for (int i = n - 1; i >= 0; --i) {
        int x = mapping[addend1[i] - 'A'];
        int y = mapping[addend2[i] - 'A'];
        int z = mapping[sum[i] - 'A'];
        if (x == -1 || y == -1 || z == -1) return false;
        if ((x + y + carry) % n != z) return false;
        carry = (x + y + carry) / n;
    }
    return carry == 0;
}

bool solve(int index) {
    if (index == n) {
        return isValid();
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            used[i] = true;
            mapping[index] = i;
            if (solve(index + 1)) return true;
            used[i] = false;
        }
    }
    return false;
}

int main() {
    cin >> n;
    cin >> addend1 >> addend2 >> sum;

    used.resize(n, false);

    solve(0);

    vector<int> result(26, -1);
    for (int i = 0; i < 26; ++i) {
        if (mapping[i] != -1) {
            result[i] = mapping[i];
        }
    }

    for (int i = 0; i < n; ++i) {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout << endl;

    return 0;
}