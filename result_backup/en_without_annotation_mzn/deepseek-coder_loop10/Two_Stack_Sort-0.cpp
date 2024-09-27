#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    vector<int> out(n);
    vector<int> action(2 * n);
    stack<int> stack1, stack2;
    int t = 0, u = 0;

    for (int i = 0; i < 2 * n; ++i) {
        if (t < n && (stack1.empty() || stack1.top() != numbers[t] + 1)) {
            stack1.push(numbers[t++]);
            action[i] = 0; // 'a'
        } else if (!stack1.empty() && stack1.top() == u + 1) {
            out[u++] = stack1.top();
            stack1.pop();
            action[i] = 1; // 'b'
        } else if (t < n && (stack2.empty() || stack2.top() != numbers[t] + 1)) {
            stack2.push(numbers[t++]);
            action[i] = 2; // 'c'
        } else if (!stack2.empty() && stack2.top() == u + 1) {
            out[u++] = stack2.top();
            stack2.pop();
            action[i] = 3; // 'd'
        }
    }

    for (int i = 0; i < 2 * n; ++i) {
        cout << (action[i] == 0 ? 'a' : action[i] == 1 ? 'b' : action[i] == 2 ? 'c' : 'd') << " ";
    }
    cout << endl;

    return 0;
}
