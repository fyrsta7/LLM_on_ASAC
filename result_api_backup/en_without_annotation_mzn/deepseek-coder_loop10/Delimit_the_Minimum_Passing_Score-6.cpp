#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Candidate {
    int id;
    int score;
};

bool compareCandidates(const Candidate &a, const Candidate &b) {
    if (a.score == b.score) {
        return a.id < b.id;
    }
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

    int num = floor(m * 1.5);
    int split = candidates[num - 1].score;
    int actual = num;

    while (actual < n && candidates[actual].score >= split) {
        ++actual;
    }

    cout << split << " " << actual << endl;
    for (int i = 0; i < actual; ++i) {
        cout << candidates[i].id << " " << candidates[i].score << endl;
    }

    return 0;
}