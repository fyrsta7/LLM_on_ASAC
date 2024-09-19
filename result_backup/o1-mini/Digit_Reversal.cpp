#include <iostream>
using namespace std;

int main(){
    int N;
    cin >> N;
    if(N == 0){
        cout << 0;
        return 0;
    }
    int sign = (N < 0) ? -1 : 1;
    int num = (N < 0) ? -N : N;
    int rev = 0;
    while(num > 0){
        rev = rev * 10 + (num % 10);
        num /= 10;
    }
    cout << sign * rev;
}