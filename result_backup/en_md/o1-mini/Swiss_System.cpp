#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Player {
    int id;
    int score;
    int w;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N, R, Q;
    cin >> N >> R >> Q;
    int total = 2*N;
    vector<Player> players(total);
    for(int i=0;i<total;i++){
        players[i].id = i+1;
    }
    for(int i=0;i<total;i++){
        cin >> players[i].score;
    }
    for(int i=0;i<total;i++){
        cin >> players[i].w;
    }
    auto cmp = [&](const Player &a, const Player &b) -> bool{
        if(a.score != b.score)
            return a.score > b.score;
        return a.id < b.id;
    };
    for(int r=0;r<R;r++){
        sort(players.begin(), players.end(), cmp);
        for(int i=0;i+1<total;i+=2){
            if(players[i].w > players[i+1].w){
                players[i].score +=1;
            }
            else{
                players[i+1].score +=1;
            }
        }
    }
    sort(players.begin(), players.end(), cmp);
    cout << players[Q-1].id;
}