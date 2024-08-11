#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    for(int i = 0; i < n; i++) {
        int fruit;
        cin >> fruit;
        minHeap.push(fruit);
    }
    
    int totalEnergy = 0;
    
    while(minHeap.size() > 1) {
        int pile1 = minHeap.top();
        minHeap.pop();
        int pile2 = minHeap.top();
        minHeap.pop();
        
        int mergeEnergy = pile1 + pile2;
        totalEnergy += mergeEnergy;
        
        minHeap.push(mergeEnergy);
    }
    
    cout << totalEnergy << endl;
    
    return 0;
}