#include <iostream>
#include <vector>
#include <algorithm>

struct Candidate {
    int reg_number;
    int score;
};

bool compare(const Candidate &a, const Candidate &b) {
    if (a.score == b.score)
        return a.reg_number < b.reg_number;
    return a.score > b.score;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<Candidate> candidates(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> candidates[i].reg_number >> candidates[i].score;
    }

    int threshold_index = (m * 3) / 2;  // 150% of m rounded down
    std::sort(candidates.begin(), candidates.end(), compare);

    int minimum_passing_score = candidates[threshold_index - 1].score;

    std::vector<Candidate> selected_candidates;
    for (const auto &candidate : candidates) {
        if (candidate.score >= minimum_passing_score) {
            selected_candidates.push_back(candidate);
        }
    }

    std::cout << minimum_passing_score << " " << selected_candidates.size() << std::endl;
    for (const auto &candidate : selected_candidates) {
        std::cout << candidate.reg_number << " " << candidate.score << std::endl;
    }

    return 0;
}