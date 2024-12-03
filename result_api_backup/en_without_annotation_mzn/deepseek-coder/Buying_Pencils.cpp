#include <iostream>
#include <algorithm>
#include <cmath>

int main() {
    int n;
    std::cin >> n;
    int pencil[3][2];
    for (int i = 0; i < 3; ++i) {
        std::cin >> pencil[i][0] >> pencil[i][1];
    }

    int min_cost = INT_MAX;
    for (int i = 0; i < 3; ++i) {
        int num_packs = std::ceil(static_cast<double>(n) / pencil[i][0]);
        int cost = num_packs * pencil[i][1];
        min_cost = std::min(min_cost, cost);
    }

    std::cout << "cost=" << min_cost << std::endl;
    return 0;
}