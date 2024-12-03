#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
    int id;
    int total_grade;
    int first_grade;
};

bool compareStudents(const Student &a, const Student &b) {
    if (a.total_grade != b.total_grade)
        return a.total_grade > b.total_grade;
    if (a.first_grade != b.first_grade)
        return a.first_grade > b.first_grade;
    return a.id < b.id;
}

int main() {
    int n;
    cin >> n;
    vector<Student> students(n);
    for (int i = 0; i < n; ++i) {
        students[i].id = i + 1;
        int g1, g2, g3;
        cin >> g1 >> g2 >> g3;
        students[i].total_grade = g1 + g2 + g3;
        students[i].first_grade = g1;
    }

    sort(students.begin(), students.end(), compareStudents);

    for (int i = 0; i < 5; ++i) {
        cout << students[i].id << " " << students[i].total_grade << endl;
    }

    return 0;
}