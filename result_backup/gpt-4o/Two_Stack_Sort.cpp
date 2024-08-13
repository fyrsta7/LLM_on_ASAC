#include <iostream>
#include <stack>
#include <vector>

using namespace std;

bool isTwoStackSortable(const vector<int> &permutation) {
    int n = permutation.size();
    vector<int> target(n);
    for (int i = 0; i < n; ++i) {
        target[i] = i + 1;
    }

    stack<int> S1, S2;
    int targetIndex = 0;

    for (int num : permutation) {
        while (!S1.empty() && S1.top() == target[targetIndex]) {
            S1.pop();
            targetIndex++;
        }
        while (!S2.empty() && S2.top() == target[targetIndex]) {
            S2.pop();
            targetIndex++;
        }

        if (num == target[targetIndex]) {
            targetIndex++;
        } else if (S1.empty() || num < S1.top()) {
            S1.push(num);
        } else if (S2.empty() || num < S2.top()) {
            S2.push(num);
        } else {
            return false;
        }
    }

    while (!S1.empty() && S1.top() == target[targetIndex]) {
        S1.pop();
        targetIndex++;
    }
    while (!S2.empty() && S2.top() == target[targetIndex]) {
        S2.pop();
        targetIndex++;
    }

    return targetIndex == n;
}

void printTwoStackSortOperations(const vector<int> &permutation) {
    int n = permutation.size();
    vector<int> target(n);
    for (int i = 0; i < n; ++i) {
        target[i] = i + 1;
    }

    stack<int> S1, S2;
    int targetIndex = 0;
    vector<char> operations;

    for (int num : permutation) {
        while (!S1.empty() && S1.top() == target[targetIndex]) {
            S1.pop();
            operations.push_back('b');
            targetIndex++;
        }
        while (!S2.empty() && S2.top() == target[targetIndex]) {
            S2.pop();
            operations.push_back('d');
            targetIndex++;
        }

        if (num == target[targetIndex]) {
            operations.push_back('a');
            operations.push_back('b');
            targetIndex++;
        } else if (S1.empty() || num < S1.top()) {
            S1.push(num);
            operations.push_back('a');
        } else if (S2.empty() || num < S2.top()) {
            S2.push(num);
            operations.push_back('c');
        }
    }

    while (!S1.empty() && S1.top() == target[targetIndex]) {
        S1.pop();
        operations.push_back('b');
        targetIndex++;
    }
    while (!S2.empty() && S2.top() == target[targetIndex]) {
        S2.pop();
        operations.push_back('d');
        targetIndex++;
    }

    for (size_t i = 0; i < operations.size(); ++i) {
        cout << operations[i];
        if (i < operations.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    vector<int> permutation(n);
    for (int i = 0; i < n; ++i) {
        cin >> permutation[i];
    }

    if (!isTwoStackSortable(permutation)) {
        cout << 0 << endl;
    } else {
        printTwoStackSortOperations(permutation);
    }

    return 0;
}