#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    int minCost = 1e9; // Start with a large number
    
    for (int i = 0; i < 3; i++) {
        int pencils, price;
        cin >> pencils >> price;
        
        int totalPackages = (n + pencils - 1) / pencils; // Calculate the number of packages needed
        int cost = totalPackages * price; // Calculate the total cost
        
        minCost = min(minCost, cost); // Update the minimum cost
    }
    
    cout << minCost << endl; // Output the minimum cost
    return 0;
}