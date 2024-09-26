#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    long long n, i, j;
    cin >> n >> i >> j;
    long long l = min({i-1, j-1, n-i, n-j});
    long long s = n - 2*l;
    long long start_num = 4*l*(n-l);
    long long number;
    if(s ==1){
        number = start_num +1;
    }
    else{
        long long offset;
        if(j == l+1 && i >= l+1 && i <=n-l){
            offset = i - (l+1);
        }
        else if(i == n-l && j > l+1 && j <=n-l){
            offset = (s-1) + (j - (l+1));
        }
        else if(j == n-l && i > l+1 && i <=n-l){
            offset = 2*(s-1) + (n-l - i);
        }
        else if(i == l+1 && j >= l+1 && j <n-l){
            offset =3*(s-1) + (n-l -j);
        }
        else{
            offset =3*(s-1) + (n-l -j);
        }
        number = start_num +1 + offset;
    }
    cout << number;
}