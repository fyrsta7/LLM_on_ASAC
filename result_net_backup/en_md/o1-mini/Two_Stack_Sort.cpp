#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> perm(n);
    for (int i = 0; i < n; ++i) {
        cin >> perm[i];
    }

    stack<int> s1, s2;
    vector<char> result;
    int next = 1; // the next number we want to output
    
    for (int i = 0; i < n;) {
        // Always try to push the current number to stack s1 first
        if (perm[i] == next) {
            result.push_back('a');
            ++next;
            ++i;
        } else if (!s1.empty() && s1.top() == next) {
            // If the top of stack s1 is the next number, pop it to the output
            result.push_back('b');
            s1.pop();
            ++next;
        } else if (perm[i] != next) {
            // Push the current element to stack s2
            result.push_back('c');
            s2.push(perm[i]);
            ++i;
        } else {
            break;
        }

        // Try to pop from stack s2 if the top is the next number
        while (!s2.empty() && s2.top() == next) {
            result.push_back('d');
            s2.pop();
            ++next;
        }
    }

    // If the sequence is not sorted properly
    if (next != n + 1) {
        cout << "0" << endl;
    } else {
        for (char op : result) {
            cout << op << " ";
        }
        cout << endl;
    }

    return 0;
}