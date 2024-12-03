#include <iostream>
#include <vector>
using namespace std;

enum op { a, b, c, d };

bool push(vector<int>& before, vector<int>& after, int element) {
    after[0] = element;
    for (int i = 1; i < before.size(); ++i) {
        after[i] = before[i - 1];
    }
    return true;
}

bool pop(vector<int>& before, vector<int>& after, int& element) {
    element = before[0];
    for (int i = 1; i < before.size(); ++i) {
        after[i - 1] = before[i];
    }
    after[before.size() - 1] = 0;
    return true;
}

bool solve(int n, vector<int>& numbers, vector<int>& out, vector<op>& action) {
    vector<vector<int>> stack1(2 * n + 2, vector<int>(n, 0));
    vector<vector<int>> stack2(2 * n + 2, vector<int>(n, 0));

    for (int i = 1; i <= 2 * n; ++i) {
        int t = 0, u = 0;
        for (int j = 0; j < i - 1; ++j) {
            if (action[j] == a || action[j] == c) ++t;
            if (action[j] == b || action[j] == d) ++u;
        }

        if (action[i - 1] == a) {
            push(stack1[i], stack1[i + 1], numbers[t]);
            stack2[i + 1] = stack2[i];
        } else if (action[i - 1] == c) {
            push(stack2[i], stack2[i + 1], numbers[t]);
            stack1[i + 1] = stack1[i];
        } else if (action[i - 1] == b) {
            pop(stack1[i], stack1[i + 1], out[u]);
            stack2[i + 1] = stack2[i];
        } else {
            pop(stack2[i], stack2[i + 1], out[u]);
            stack1[i + 1] = stack1[i];
        }
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    vector<int> out(n, 0);
    vector<op> action(2 * n, a);

    if (solve(n, numbers, out, action)) {
        for (auto& act : action) {
            cout << static_cast<char>('a' + act) << " ";
        }
        cout << endl;
    } else {
        cout << "No solution" << endl;
    }

    return 0;
}