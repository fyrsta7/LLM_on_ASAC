#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
    int id;
    int total;
    int first_grade;

    bool operator<(const Student& other) const {
        if (total != other.total) return total > other.total;
        if (first_grade != other.first_grade) return first_grade > other.first_grade;
        return id < other.id;
    }
};

int main() {
    int n;
    cin >> n;
    vector<Student> students(n);

    for (int i = 0; i < n; ++i) {
        students[i].id = i + 1;
        cin >> students[i].first_grade;
        int grade2, grade3;
        cin >> grade2 >> grade3;
        students[i].total = students[i].first_grade + grade2 + grade3;
    }

    sort(students.begin(), students.end());

    for (int i = 0; i < 5; ++i) {
        cout << students[i].id << " " << students[i].total << endl;
    }

    return 0;
}