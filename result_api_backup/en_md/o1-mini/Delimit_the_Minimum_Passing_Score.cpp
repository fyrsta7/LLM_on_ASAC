#include <iostream>
#include <vector>
#include <algorithm>

struct Candidate {
    int reg;
    int score;
};

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n, m;
    std::cin >> n >> m;
    std::vector<Candidate> candidates(n);
    for(int i=0;i<n;i++) {
        std::cin >> candidates[i].reg >> candidates[i].score;
    }
    std::sort(candidates.begin(), candidates.end(), [&](const Candidate &a, const Candidate &b) -> bool{
        if(a.score != b.score)
            return a.score > b.score;
        return a.reg < b.reg;
    });
    int x = (3 * m) / 2;
    int min_pass_score = candidates[x-1].score;
    std::vector<Candidate> selected;
    for(auto &c : candidates){
        if(c.score >= min_pass_score){
            selected.push_back(c);
        }
    }
    std::cout << min_pass_score << " " << selected.size() << "\n";
    for(auto &c : selected){
        std::cout << c.reg << " " << c.score << "\n";
    }
}