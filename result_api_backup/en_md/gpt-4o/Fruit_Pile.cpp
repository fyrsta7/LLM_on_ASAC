#include <iostream>
#include <vector>
#include <queue>

int main() {
    int n;
    std::cin >> n;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    
    for (int i = 0; i < n; ++i) {
        int weight;
        std::cin >> weight;
        minHeap.push(weight);
    }
    
    int totalEnergy = 0;
    while (minHeap.size() > 1) {
        int pile1 = minHeap.top(); minHeap.pop();
        int pile2 = minHeap.top(); minHeap.pop();
        int mergedPile = pile1 + pile2;
        totalEnergy += mergedPile;
        minHeap.push(mergedPile);
    }
    
    std::cout << totalEnergy << std::endl;
    return 0;
}