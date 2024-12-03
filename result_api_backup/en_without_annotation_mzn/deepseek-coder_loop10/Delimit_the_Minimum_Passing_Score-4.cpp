#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Participant {
    int id;
    int score;
};

bool compareParticipants(const Participant &a, const Participant &b) {
    if (a.score == b.score) {
        return a.id < b.id;
    }
    return a.score > b.score;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Participant> participants(n);
    for (int i = 0; i < n; ++i) {
        cin >> participants[i].id >> participants[i].score;
    }

    sort(participants.begin(), participants.end(), compareParticipants);

    int num = floor(m * 1.5);
    int split = participants[num - 1].score;
    int actual = 0;

    for (int i = 0; i < n; ++i) {
        if (participants[i].score >= split) {
            actual++;
        } else {
            break;
        }
    }

    cout << split << " " << actual << endl;
    for (int i = 0; i < actual; ++i) {
        cout << participants[i].id << " " << participants[i].score << endl;
    }

    return 0;
}