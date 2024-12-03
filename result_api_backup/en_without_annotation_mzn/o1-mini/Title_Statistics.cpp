#include <bits/stdc++.h>
using namespace std;

int main(){
    string title;
    getline(cin, title);
    int answer = 0;
    for(char c : title){
        if(c != ' ') answer++;
    }
    cout << answer;
}