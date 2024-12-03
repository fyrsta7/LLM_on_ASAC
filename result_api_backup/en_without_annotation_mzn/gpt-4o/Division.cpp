#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int n;
vector<int> a;

int calculateSum(const vector<int>& part) {
    int sum = 0;
    for (int num : part) {
        sum += num;
    }
    return sum;
}

int calculateSquaredSum(const vector<int>& part) {
    int sum = calculateSum(part);
    return sum * sum;
}

void findOptimalPartition(int start, int end, vector<int>& partition, int currentPartSum, int& minCost, vector<vector<int>>& bestPartition) {
    if (start > n) {
        int cost = 0;
        for (const auto& part : partition) {
            cost += calculateSquaredSum(part);
        }
        if (cost < minCost) {
            minCost = cost;
            bestPartition = partition;
        }
        return;
    }
    
    for (int i = start; i <= end; ++i) {
        partition.push_back(vector<int>(a.begin() + start - 1, a.begin() + i));
        findOptimalPartition(i + 1, end, partition, currentPartSum + a[i], minCost, bestPartition);
        partition.pop_back();
    }
}

int main() {
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    int minCost = INT_MAX;
    vector<vector<int>> partition, bestPartition;
    findOptimalPartition(1, n, partition, 0, minCost, bestPartition);
    
    cout << minCost << endl;
    
    return 0;
}