#include <bits/stdc++.h>
using namespace std;

struct Student {
    int id;
    int score;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<Student> students(n);
    int max_score = 0;
    for(int i=0;i<n;i++){
        cin >> students[i].id >> students[i].score;
        if(students[i].score > max_score) max_score = students[i].score;
    }
    int num = (3 * m) / 2;
    int split = 1;
    for(int s=max_score;s>=1;s--){
        int cnt=0;
        for(auto &stu: students){
            if(stu.score >= s) cnt++;
        }
        if(cnt >= num){
            split = s;
            break;
        }
    }
    vector<Student> pass;
    for(auto &stu: students){
        if(stu.score >= split){
            pass.push_back(stu);
        }
    }
    sort(pass.begin(), pass.end(), [&](const Student &a, const Student &b) -> bool{
        if(a.score != b.score) return a.score > b.score;
        return a.id < b.id;
    });
    int actual = pass.size();
    cout << split << " " << actual << "\n";
    for(auto &stu: pass){
        cout << stu.id << " " << stu.score << "\n";
    }
}