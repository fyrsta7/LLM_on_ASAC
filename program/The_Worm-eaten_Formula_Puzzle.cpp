#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

int n;
string first, second, result;
vector<int> mapping(26, -1);
vector<bool> used;

bool is_valid() {
    int carry = 0;
    for (int i = n - 1; i >= 0; --i) {
        int val1 = mapping[first[i] - 'A'];
        int val2 = mapping[second[i] - 'A'];
        int res = mapping[result[i] - 'A'];
        if ((val1 + val2 + carry) % n != res) return false;
        carry = (val1 + val2 + carry) / n;
    }
    return carry == 0;
}

bool solve(int idx) {
    if (idx == n) return is_valid();

    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            used[i] = true;
            mapping[idx] = i;
            if (solve(idx + 1)) return true;
            used[i] = false;
            mapping[idx] = -1;
        }
    }
    return false;
}

int main() {
    cin >> n;
    cin >> first >> second >> result;

    used.resize(n, false);

    solve(0);

    for (int i = 0; i < n; ++i) {
        cout << mapping[i] << " ";
    }
    cout << endl;

    return 0;
}