#include <iostream>
#include <string>
#include <cstdint>

using namespace std;

int main(){
    unsigned long long n;
    unsigned long long k;
    cin >> n >> k;
    unsigned long long G = k ^ (k >> 1);
    string s;
    for(int i = n-1; i >= 0; i--){
        s += (G & (1ULL << i)) ? '1' : '0';
    }
    cout << s << endl;
}