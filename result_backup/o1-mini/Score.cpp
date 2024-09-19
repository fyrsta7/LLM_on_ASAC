#include <iostream>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int A, B, C;
    cin >> A >> B >> C;
    long long total = (long long)A * 20 + (long long)B * 30 + (long long)C * 50;
    cout << (total / 100);
}