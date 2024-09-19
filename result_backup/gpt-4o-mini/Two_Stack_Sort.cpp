#include <iostream>
#include <stack>
#include <vector>

using namespace std;

void generateOperations(int n, const vector<int>& permutation) {
    stack<int> s1, s2;
    vector<char> operations;
    int index = 0;
    
    for (int i = 1; i <= n; ++i) {
        while (index < n && permutation[index] != i) {
            s1.push(permutation[index++]);
            operations.push_back('a');
        }
        if (index < n && permutation[index] == i) {
            operations.push_back('a');
            operations.push_back('b');
            index++;
        }

        while (!s1.empty() && s1.top() == i) {
            operations.push_back('b');
            s1.pop();
        }

        while (!s2.empty() && s2.top() == i) {
            operations.push_back('d');
            s2.pop();
        }

        if (index < n && permutation[index] < i) {
            cout << 0;
            return;
        }

        if (index < n) {
            s2.push(permutation[index++]);
            operations.push_back('c');
        }
    }

    while (!s2.empty()) {
        if (s2.top() == n) {
            operations.push_back('d');
            s2.pop();
            n--;
        } else {
            cout << 0;
            return;
        }
    }

    cout << operations.size() << endl;
    for (char op : operations) {
        cout << op << " ";
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> permutation(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> permutation[i];
    }

    generateOperations(n, permutation);

    return 0;
}