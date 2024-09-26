#include <iostream>
#include <vector>
#include <algorithm>

struct Student {
    int number;
    int chinese;
    int math;
    int english;
    int total;
};

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    std::cin >> n;
    std::vector<Student> students;
    students.reserve(n);
    for(int i=1;i<=n;i++){
        int c, m, e;
        std::cin >> c >> m >> e;
        Student s;
        s.number = i;
        s.chinese = c;
        s.math = m;
        s.english = e;
        s.total = c + m + e;
        students.push_back(s);
    }
    std::sort(students.begin(), students.end(), [&](const Student& a, const Student& b) -> bool{
        if(a.total != b.total){
            return a.total > b.total;
        }
        if(a.chinese != b.chinese){
            return a.chinese > b.chinese;
        }
        return a.number < b.number;
    });
    int output_count = std::min(5, n);
    for(int i=0;i<output_count;i++){
        std::cout << students[i].number << " " << students[i].total << "\n";
    }
    return 0;
}