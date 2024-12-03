#include <iostream>
#include <vector>
#include <limits.h>

// Function to determine if the road exists between two nodes
bool roadExists(const std::vector<std::pair<int, int>> &roads, int start, int end) {
    for (const auto &road : roads) {
        if ((road.first == start && road.second == end) || (road.second == start && road.first == end)) {
            return true;
        }
    }
    return false;
}

// Function to calculate the score based on troops and power
int calculateScore(const std::vector<int> &troops, const std::vector<int> &power) {
    int score = 0;
    for (size_t i = 0; i < troops.size(); ++i) {
        score += troops[i] * power[i];
    }
    return score;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> p(n);
    std::vector<std::pair<int, int>> roads(n - 1);
    std::vector<std::tuple<int, int, int, int>> requests(m);
    
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i];
    }
    
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        roads[i] = {a, b};
    }
    
    for (int i = 0; i < m; ++i) {
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        requests[i] = {a, b, c, d};
    }
    
    std::vector<int> finalScores(m, 0);
    
    for (int i = 0; i < m; ++i) {
        auto [a, b, c, d] = requests[i];
        
        if (b == 0 && d == 0 && roadExists(roads, a, c)) {
            finalScores[i] = -1;
        } else {
            std::vector<int> troops(n, 0);
            troops[a - 1] = b;
            troops[c - 1] = d;
            
            bool valid = true;
            
            for (const auto &road : roads) {
                if (troops[road.first - 1] == 0 && troops[road.second - 1] == 0) {
                    valid = false;
                    break;
                }
            }
            
            if (valid) {
                finalScores[i] = calculateScore(troops, p);
            } else {
                finalScores[i] = -1;
            }
        }
    }
    
    int minScoreSum = INT_MAX;
    for (int i = 0; i < m; ++i) {
        if (finalScores[i] != -1) {
            minScoreSum = std::min(minScoreSum, finalScores[i]);
        }
    }

    std::cout << minScoreSum << std::endl;

    return 0;
}