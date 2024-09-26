#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> face(n+1);
    for(int i=1;i<=n;i++) cin >> face[i];
    vector<string> person(n+1);
    for(int i=1;i<=n;i++) cin >> person[i];
    // Read instructions
    struct Instruction{
        int x;
        int y;
    };
    vector<Instruction> instructions(m);
    for(int i=0;i<m;i++) cin >> instructions[i].x >> instructions[i].y;
    // Initialize state
    int s =1;
    // Process instructions
    for(int i=0;i<m;i++){
        int x = instructions[i].x;
        int y = instructions[i].y;
        if( (face[s]==0 && x==0) || (face[s]==1 && x==1)){
            // cw
            s = (s + n - y -1) % n +1;
        }
        else{
            // ccw
            s = (s + y -1) % n +1;
        }
    }
    cout << person[s];
}