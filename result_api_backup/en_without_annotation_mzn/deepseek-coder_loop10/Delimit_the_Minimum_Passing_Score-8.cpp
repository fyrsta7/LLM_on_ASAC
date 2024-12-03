#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Contestant {
    int id;
    int score;
};

bool compareContestants(const Contestant &a, const Contestant &b) {
    if (a.score == b.score) return a.id < b.id;
    return a.score > b.score;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Contestant> contestants(n);
    for (int i = 0; i < n; ++i) {
        cin >> contestants[i].id >> contestants[i].score;
    }

    sort(contestants.begin(), contestants.end(), compareContestants);

    int num = m * 1.5;
    int split = contestants[num - 1].score;
    int actual = num;

    while (actual < n && contestants[actual].score >= split) {
        ++actual;
    }

    cout << split << " " << actual << endl;
    for (int i = 0; i < actual; ++i) {
        cout << contestants[i].id << " " << contestants[i].score << endl;
    }

    return 0;
}