#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n;
    cin >> n;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    for (int i = 0; i < n; i++) {
        int fruit;
        cin >> fruit;
        minHeap.push(fruit);
    }
    
    int totalEnergy = 0;
    
    while (minHeap.size() > 1) {
        int first = minHeap.top(); minHeap.pop();
        int second = minHeap.top(); minHeap.pop();
        
        int merged = first + second;
        totalEnergy += merged;
        minHeap.push(merged);
    }
    
    cout << totalEnergy << endl;
    
    return 0;
}