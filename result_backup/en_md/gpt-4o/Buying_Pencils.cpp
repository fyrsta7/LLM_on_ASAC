#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n, p1, p2, p3, c1, c2, c3;
    cin >> n;
    cin >> p1 >> c1;
    cin >> p2 >> c2;
    cin >> p3 >> c3;
    
    int min_cost = INT_MAX;
    
    min_cost = min(min_cost, ((n + p1 - 1) / p1) * c1);
    min_cost = min(min_cost, ((n + p2 - 1) / p2) * c2);
    min_cost = min(min_cost, ((n + p3 - 1) / p3) * c3);
    
    cout << min_cost << endl;
    return 0;
}