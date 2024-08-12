#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> permutation(n);
    for (int i = 0; i < n; ++i) {
        cin >> permutation[i];
    }

    stack<int> s1, s2;
    vector<char> operations;
    int expected = 1;

    for (int i = 0; i < n; ++i) {
        if (permutation[i] == expected) {
            operations.push_back('a');
            operations.push_back('b');
            ++expected;
            while ((!s1.empty() && s1.top() == expected) || (!s2.empty() && s2.top() == expected)) {
                if (!s1.empty() && s1.top() == expected) {
                    operations.push_back('b');
                    s1.pop();
                } else {
                    operations.push_back('d');
                    s2.pop();
                }
                ++expected;
            }
        } else {
            if (s1.empty() || permutation[i] < s1.top()) {
                s1.push(permutation[i]);
                operations.push_back('a');
            } else {
                s2.push(permutation[i]);
                operations.push_back('c');
            }
        }
    }

    if (expected == n + 1) {
        for (size_t i = 0; i < operations.size(); ++i) {
            if (i > 0) cout << ' ';
            cout << operations[i];
        }
        cout << endl;
    } else {
        cout << 0 << endl;
    }

    return 0;
}
