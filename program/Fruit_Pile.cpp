#include <iostream>
#include <queue>
#include <functional>

using namespace std;

int main() {
    int n;
    cin >> n;

    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        pq.push(num);
    }

    long long cost = 0;

    while (pq.size() > 1) {
        int first = pq.top();
        pq.pop();
        int second = pq.top();
        pq.pop();
        
        int sum = first + second;
        cost += sum;
        
        pq.push(sum);
    }

    cout << cost << endl;

    return 0;
}