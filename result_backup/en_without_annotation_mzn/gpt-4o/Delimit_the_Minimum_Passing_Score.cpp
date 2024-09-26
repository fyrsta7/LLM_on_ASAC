#include <iostream>
#include <vector>
#include <algorithm>

struct Participant {
    int id;
    int score;
};

bool scoreComparator(const Participant &a, const Participant &b) {
    if (a.score == b.score) {
        return a.id < b.id;
    }
    return a.score > b.score;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<Participant> participants(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> participants[i].id;
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> participants[i].score;
    }

    int num = static_cast<int>(m * 1.5);

    std::sort(participants.begin(), participants.end(), scoreComparator);

    int split = participants[num - 1].score;
    int actual = 0;

    for (const Participant &p : participants) {
        if (p.score >= split) {
            actual++;
        }
    }

    if (actual >= num) {
        std::cout << split << " " << actual << "\n";
        for (int i = 0; i < actual; ++i) {
            std::cout << participants[i].id << " " << participants[i].score << "\n";
        }
    }

    return 0;
}