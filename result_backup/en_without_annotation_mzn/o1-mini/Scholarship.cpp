#include <bits/stdc++.h>
using namespace std;

struct Student {
    int index;
    int sum;
    int grade1;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<Student> students(n);
    for(int i=0;i<n;i++){
        int g1, g2, g3;
        cin >> g1 >> g2 >> g3;
        students[i].index = i+1;
        students[i].sum = g1 + g2 + g3;
        students[i].grade1 = g1;
    }
    sort(students.begin(), students.end(), [&](const Student &a, const Student &b) -> bool{
        if(a.sum != b.sum) return a.sum > b.sum;
        if(a.grade1 != b.grade1) return a.grade1 > b.grade1;
        return a.index < b.index;
    });
    int output_count = min(5, n);
    for(int i=0;i<output_count;i++) cout << students[i].index << " " << students[i].sum << "\n";
}