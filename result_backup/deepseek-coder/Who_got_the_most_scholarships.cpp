#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Student {
    string name;
    int avgScore;
    int clsEvalScore;
    bool isLeader;
    bool isFromWest;
    int papers;
    int scholarship;
};

int main() {
    int N;
    cin >> N;
    vector<Student> students(N);
    int totalScholarship = 0;
    string topStudent;
    int maxScholarship = 0;

    for (int i = 0; i < N; ++i) {
        cin >> students[i].name >> students[i].avgScore >> students[i].clsEvalScore;
        char leader, fromWest;
        cin >> leader >> fromWest >> students[i].papers;
        students[i].isLeader = (leader == 'Y');
        students[i].isFromWest = (fromWest == 'Y');

        students[i].scholarship = 0;
        if (students[i].avgScore > 80 && students[i].papers > 0) students[i].scholarship += 8000;
        if (students[i].avgScore > 85 && students[i].clsEvalScore > 80) students[i].scholarship += 4000;
        if (students[i].avgScore > 90) students[i].scholarship += 2000;
        if (students[i].avgScore > 85 && students[i].isFromWest) students[i].scholarship += 1000;
        if (students[i].clsEvalScore > 80 && students[i].isLeader) students[i].scholarship += 850;

        totalScholarship += students[i].scholarship;
        if (students[i].scholarship > maxScholarship) {
            maxScholarship = students[i].scholarship;
            topStudent = students[i].name;
        }
    }

    cout << topStudent << endl;
    cout << maxScholarship << endl;
    cout << totalScholarship << endl;

    return 0;
}
