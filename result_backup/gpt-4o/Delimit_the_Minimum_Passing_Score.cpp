#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Candidate {
    int id;
    int score;
};

bool compareCandidates(const Candidate &a, const Candidate &b) {
    if (a.score == b.score) return a.id < b.id;
    return a.score > b.score;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Candidate> candidates(n);

    for (int i = 0; i < n; ++i) {
        cin >> candidates[i].id >> candidates[i].score;
    }

    sort(candidates.begin(), candidates.end(), compareCandidates);

    int limit = m * 3 / 2;
    int minPassingScore = candidates[limit - 1].score;

    vector<Candidate> selectedCandidates;
    for (int i = 0; i < n; ++i) {
        if (candidates[i].score >= minPassingScore) {
            selectedCandidates.push_back(candidates[i]);
        }
    }

    cout << minPassingScore << " " << selectedCandidates.size() << endl;
    for (const auto &candidate : selectedCandidates) {
        cout << candidate.id << " " << candidate.score << endl;
    }

    return 0;
}