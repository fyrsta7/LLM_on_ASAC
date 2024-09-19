#include <iostream>
#include <string>

using namespace std;

string S;
int N;

char getType(int l, int r) {
    bool has0 = false, has1 = false;
    for(int i = l; i < r; ++i){
        if(S[i] == '0') has0 = true;
        if(S[i] == '1') has1 = true;
        if(has0 && has1) return 'F';
    }
    if(has0) return 'B';
    return 'I';
}

string postOrderTraversal(int l, int r){
    if(l >= r) return "";
    char type = getType(l, r);
    if(r - l == 1){
        return string(1, type);
    }
    int mid = l + (r - l)/2;
    string left = postOrderTraversal(l, mid);
    string right = postOrderTraversal(mid, r);
    return left + right + string(1, type);
}

int main(){
    cin >> N;
    cin >> S;
    string result = postOrderTraversal(0, 1<<N);
    cout << result;
}
