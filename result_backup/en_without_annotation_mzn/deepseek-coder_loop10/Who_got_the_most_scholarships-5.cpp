#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int fellow(int score, int paper) {
    return (score > 80 && paper >= 1) ? 8000 : 0;
}

int mayfourth(int score, int review) {
    return (score > 85 && review > 80) ? 4000 : 0;
}

int grade(int score) {
    return (score > 90) ? 2000 : 0;
}

int west(int score, const string& if_west) {
    return (score > 85 && if_west == "Y") ? 1000 : 0;
}

int contribution(int review, const string& if_leader) {
    return (review > 80 && if_leader == "Y") ? 850 : 0;
}

int main() {
    int n;
    cin >> n;
    
    vector<string> name(n);
    vector<int> score(n);
    vector<int> review(n);
    vector<string> if_leader(n);
    vector<string> if_west(n);
    vector<int> paper(n);
    vector<int> scholarship(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> name[i] >> score[i] >> review[i] >> if_leader[i] >> if_west[i] >> paper[i];
        scholarship[i] = fellow(score[i], paper[i]) + mayfourth(score[i], review[i]) + grade(score[i]) + west(score[i], if_west[i]) + contribution(review[i], if_leader[i]);
    }
    
    int max_scholarship = *max_element(scholarship.begin(), scholarship.end());
    int total_scholarship = accumulate(scholarship.begin(), scholarship.end(), 0);
    int max_index = max_element(scholarship.begin(), scholarship.end()) - scholarship.begin();
    
    cout << name[max_index] << endl;
    cout << max_scholarship << endl;
    cout << total_scholarship << endl;
    
    return 0;
}