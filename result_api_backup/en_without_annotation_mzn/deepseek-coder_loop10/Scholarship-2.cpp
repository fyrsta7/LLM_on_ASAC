#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
    int id;
    int total;
    int grade1;
};

bool compareStudents(const Student &a, const Student &b) {
    if (a.total != b.total) return a.total > b.total;
    if (a.grade1 != b.grade1) return a.grade1 > b.grade1;
    return a.id < b.id;
}

int main() {
    int n;
    cin >> n;
    vector<Student> students(n);

    for (int i = 0; i < n; ++i) {
        students[i].id = i + 1;
        cin >> students[i].grade1;
        int grade2, grade3;
        cin >> grade2 >> grade3;
        students[i].total = students[i].grade1 + grade2 + grade3;
    }

    sort(students.begin(), students.end(), compareStudents);

    for (int i = 0; i < 5; ++i) {
        cout << students[i].id << " " << students[i].total << endl;
    }

    return 0;
}