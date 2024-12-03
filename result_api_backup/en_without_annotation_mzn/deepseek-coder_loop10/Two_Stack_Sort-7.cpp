#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        numbers[i] = i + 1;
    }

    vector<int> out(n);
    vector<char> action(2 * n);
    stack<int> stack1, stack2;
    int t = 0, u = 0;

    for (int i = 0; i < 2 * n; ++i) {
        if (t < n && (stack1.empty() || stack1.top() != u + 1)) {
            action[i] = 'a';
            stack1.push(numbers[t++]);
        } else if (!stack1.empty() && stack1.top() == u + 1) {
            action[i] = 'b';
            out[u++] = stack1.top();
            stack1.pop();
        } else if (t < n && (stack2.empty() || stack2.top() != u + 1)) {
            action[i] = 'c';
            stack2.push(numbers[t++]);
        } else if (!stack2.empty() && stack2.top() == u + 1) {
            action[i] = 'd';
            out[u++] = stack2.top();
            stack2.pop();
        }
    }

    for (int i = 0; i < 2 * n; ++i) {
        cout << action[i];
    }
    cout << endl;

    return 0;
}
