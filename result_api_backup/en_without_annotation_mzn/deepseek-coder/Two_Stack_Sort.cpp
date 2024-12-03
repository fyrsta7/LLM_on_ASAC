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

    vector<char> action(2 * n);
    stack<int> stack1, stack2;
    int out_index = 0;

    for (int i = 0; i < 2 * n; ++i) {
        if (!stack1.empty() && stack1.top() == out_index + 1) {
            stack1.pop();
            action[i] = 'b';
            ++out_index;
        } else if (!stack2.empty() && stack2.top() == out_index + 1) {
            stack2.pop();
            action[i] = 'd';
            ++out_index;
        } else if (stack1.size() < n && (stack2.empty() || stack1.size() <= stack2.size())) {
            stack1.push(numbers[stack1.size()]);
            action[i] = 'a';
        } else {
            stack2.push(numbers[stack2.size()]);
            action[i] = 'c';
        }
    }

    for (char c : action) {
        cout << c;
    }
    cout << endl;

    return 0;
}
