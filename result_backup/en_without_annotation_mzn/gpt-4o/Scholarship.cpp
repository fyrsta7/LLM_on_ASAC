#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
    int id;
    int grades[3];
    int total() const {
        return grades[0] + grades[1] + grades[2];
    }
};

bool comparator(const Student& a, const Student& b) {
    if(a.total() != b.total())
        return a.total() > b.total();
    if(a.grades[0] != b.grades[0])
        return a.grades[0] > b.grades[0];
    return a.id < b.id;
}

int main() {
    int n;
    cin >> n;
    vector<Student> students(n);
    
    for (int i = 0; i < n; i++) {
        students[i].id = i + 1;
        for (int j = 0; j < 3; j++) {
            cin >> students[i].grades[j];
        }
    }
    
    sort(students.begin(), students.end(), comparator);
    
    for (int i = 0; i < min(5, n); i++) {
        cout << students[i].id << " " << students[i].total() << endl;
    }
    
    return 0;
}