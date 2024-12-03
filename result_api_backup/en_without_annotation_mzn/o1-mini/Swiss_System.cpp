#include <bits/stdc++.h>
using namespace std;

struct Element {
    int id;
    int w;
    long long score;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, R, Q;
    cin >> N >> R >> Q;
    int size = 2*N;
    vector<long long> s(size);
    for(auto &x: s) cin >> x;
    vector<int> w(size);
    for(auto &x: w) cin >> x;
    vector<Element> elems(size);
    for(int i=0;i<size;i++) {
        elems[i].id = i+1;
        elems[i].w = w[i];
        elems[i].score = s[i];
    }
    // Initial sort
    sort(elems.begin(), elems.end(), [&](const Element &a, const Element &b) -> bool{
        if(a.score != b.score) return a.score > b.score;
        return a.id < b.id;
    });
    for(int r=0;r<R;r++){
        // Pair and update scores
        for(int i=0;i<size;i+=2){
            int a = elems[i].id;
            int b = elems[i+1].id;
            if(w[a-1] > w[b-1]) elems[i].score +=1;
            else elems[i+1].score +=1;
        }
        // Sort again
        sort(elems.begin(), elems.end(), [&](const Element &a, const Element &b) -> bool{
            if(a.score != b.score) return a.score > b.score;
            return a.id < b.id;
        });
    }
    if(Q >=1 && Q <= size){
        cout << elems[Q-1].id;
    }
    return 0;
}