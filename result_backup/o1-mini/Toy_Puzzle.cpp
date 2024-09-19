#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Toy {
    int orientation;
    string profession;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<Toy> toys(n);
    for(int i=0;i<n;i++) {
        cin >> toys[i].orientation >> toys[i].profession;
    }
    int current =0;
    for(int i=0;i<m;i++){
        int a, s;
        cin >> a >> s;
        int ori = toys[current].orientation;
        int direction;
        if(a ==0){
            if(ori ==0) direction = -1;
            else direction = +1;
        }
        else{
            if(ori ==0) direction = +1;
            else direction = -1;
        }
        if(direction ==1){
            current +=s;
            if(current >=n) current -=n;
        }
        else{
            current -=s;
            if(current <0) current +=n;
        }
    }
    cout << toys[current].profession;
}