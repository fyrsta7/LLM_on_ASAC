#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
    int id;
    int chinese;
    int math;
    int english;
    int total;
};

bool compare(const Student &a, const Student &b) {
    if (a.total != b.total) return a.total > b.total;
    if (a.chinese != b.chinese) return a.chinese > b.chinese;
    return a.id < b.id;
}

int main() {
    int n;
    cin >> n;
    vector<Student> students(n);
    
    for (int i = 0; i < n; i++) {
        students[i].id = i + 1;
        cin >> students[i].chinese >> students[i].math >> students[i].english;
        students[i].total = students[i].chinese + students[i].math + students[i].english;
    }
    
    sort(students.begin(), students.end(), compare);
    
    for (int i = 0; i < 5; i++) {
        cout << students[i].id << " " << students[i].total << endl;
    }
    
    return 0;
}