#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
    int index;
    int total_grade;
    int first_grade;
};

bool compareStudents(const Student &a, const Student &b) {
    if (a.total_grade != b.total_grade)
        return a.total_grade > b.total_grade;
    if (a.first_grade != b.first_grade)
        return a.first_grade > b.first_grade;
    return a.index < b.index;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> grades(n, vector<int>(3));
    vector<Student> students(n);

    for (int i = 0; i < n; ++i) {
        cin >> grades[i][0] >> grades[i][1] >> grades[i][2];
        students[i].index = i + 1;
        students[i].total_grade = grades[i][0] + grades[i][1] + grades[i][2];
        students[i].first_grade = grades[i][0];
    }

    sort(students.begin(), students.end(), compareStudents);

    for (int i = 0; i < 5; ++i) {
        cout << students[i].index << " " << students[i].total_grade << endl;
    }

    return 0;
}