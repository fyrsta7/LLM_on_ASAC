#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
    int id;
    int totalScore;
    int chineseScore;

    bool operator<(const Student& other) const {
        if (totalScore != other.totalScore) 
            return totalScore > other.totalScore;
        if (chineseScore != other.chineseScore) 
            return chineseScore > other.chineseScore;
        return id < other.id;
    }
};

int main() {
    int n;
    cin >> n;
    vector<Student> students(n);

    for (int i = 0; i < n; ++i) {
        int chinese, math, english;
        cin >> chinese >> math >> english;
        students[i] = {i + 1, chinese + math + english, chinese};
    }

    sort(students.begin(), students.end());

    for (int i = 0; i < 5; ++i) {
        cout << students[i].id << " " << students[i].totalScore << endl;
    }

    return 0;
}