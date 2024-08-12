#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Candidate {
    int regNum;
    int score;
};

bool compare(const Candidate &a, const Candidate &b) {
    if (a.score != b.score) return a.score > b.score;
    return a.regNum < b.regNum;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Candidate> candidates(n);
    for (int i = 0; i < n; ++i) {
        cin >> candidates[i].regNum >> candidates[i].score;
    }
    sort(candidates.begin(), candidates.end(), compare);
    int passCount = m * 1.5;
    int minPassScore = candidates[passCount - 1].score;
    int actualPassCount = 0;
    for (int i = 0; i < n; ++i) {
        if (candidates[i].score >= minPassScore) {
            actualPassCount++;
        } else {
            break;
        }
    }
    cout << minPassScore << " " << actualPassCount << endl;
    for (int i = 0; i < actualPassCount; ++i) {
        cout << candidates[i].regNum << " " << candidates[i].score << endl;
    }
    return 0;
}
