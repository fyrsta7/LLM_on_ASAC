#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> S(n), A(n);

    for (int i = 0; i < n; ++i)
        cin >> S[i];
    for (int i = 0; i < n; ++i)
        cin >> A[i];

    vector<vector<int>> choose(n, vector<int>(n, 0));
    vector<int> r(n), c(n);

    auto valid = [&](int i) {
        return choose[i][r[i]] == 1 && accumulate(choose[i].begin(), choose[i].begin() + r[i], 0) == i + 1;
    };

    auto cost = [&](int i) {
        return accumulate(choose[i].begin(), choose[i].begin() + r[i], 0, [&](int acc, int x) {
            return acc + x * A[&x - &choose[i][0]];
        }) + S[r[i]] * 2;
    };

    for (int i = 0; i < n; ++i) {
        r[i] = i;  // Initialize r as identity mapping.
        choose[i][i] = 1;  // Make minimum valid selections.
        if (valid(i)) {
            c[i] = cost(i);
        }
    }

    int result = accumulate(c.begin(), c.end(), 0);

    for (int i = 0; i < n; ++i) {
        cout << c[i] << " ";
    }
    cout << endl << result << endl;

    return 0;
}