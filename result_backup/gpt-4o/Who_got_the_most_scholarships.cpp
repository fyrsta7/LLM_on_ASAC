#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct Student {
    string name;
    int finalScore;
    int classScore;
    char isLeader;
    char isFromWest;
    int papers;
};

int calculateScholarship(const Student& student) {
    int total = 0;
    if (student.finalScore > 80 && student.papers > 0) {
        total += 8000;
    }
    if (student.finalScore > 85 && student.classScore > 80) {
        total += 4000;
    }
    if (student.finalScore > 90) {
        total += 2000;
    }
    if (student.isFromWest == 'Y' && student.finalScore > 85) {
        total += 1000;
    }
    if (student.isLeader == 'Y' && student.classScore > 80) {
        total += 850;
    }
    return total;
}

int main() {
    int n;
    cin >> n;
    vector<Student> students(n);
    string name;
    int finalScore, classScore, papers;
    char isLeader, isFromWest;
    int maxScholarship = 0, maxIndex = -1, totalScholarship = 0;

    for (int i = 0; i < n; ++i) {
        cin >> students[i].name >> students[i].finalScore >> students[i].classScore >> students[i].isLeader >> students[i].isFromWest >> students[i].papers;
        int scholarship = calculateScholarship(students[i]);
        totalScholarship += scholarship;
        if (scholarship > maxScholarship) {
            maxScholarship = scholarship;
            maxIndex = i;
        }
    }

    cout << students[maxIndex].name << endl;
    cout << maxScholarship << endl;
    cout << totalScholarship << endl;

    return 0;
}