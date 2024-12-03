#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Student {
    string name;
    int score;
    int review;
    string if_leader;
    string if_west;
    int paper;
    int scholarship;
};

int fellow(int score, int paper) {
    return (score > 80 && paper >= 1) ? 8000 : 0;
}

int mayfourth(int score, int review) {
    return (score > 85 && review > 80) ? 4000 : 0;
}

int grade(int score) {
    return (score > 90) ? 2000 : 0;
}

int west(int score, const string &if_west) {
    return (score > 85 && if_west == "Y") ? 1000 : 0;
}

int contribution(int review, const string &if_leader) {
    return (review > 80 && if_leader == "Y") ? 850 : 0;
}

void calculate_scholarship(Student &student) {
    student.scholarship = fellow(student.score, student.paper) + 
                          mayfourth(student.score, student.review) +
                          grade(student.score) +
                          west(student.score, student.if_west) +
                          contribution(student.review, student.if_leader);
}

int main() {
    int n;
    cin >> n;
    vector<Student> students(n);

    for (int i = 0; i < n; ++i) {
        cin >> students[i].name >> students[i].score >> students[i].review >> students[i].if_leader >> students[i].if_west >> students[i].paper;
    }

    for (int i = 0; i < n; ++i) {
        calculate_scholarship(students[i]);
    }

    int max_scholarship_index = 0;
    int total_scholarship = 0;

    for (int i = 0; i < n; ++i) {
        if (students[i].scholarship > students[max_scholarship_index].scholarship) {
            max_scholarship_index = i;
        }
        total_scholarship += students[i].scholarship;
    }

    cout << students[max_scholarship_index].name << endl;
    cout << students[max_scholarship_index].scholarship << endl;
    cout << total_scholarship << endl;

    return 0;
}