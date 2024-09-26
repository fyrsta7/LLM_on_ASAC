#include <iostream>
using namespace std;

int main(){
    int L, R;
    cin >> L >> R;
    int count = 0;
    for(int i = L; i <= R; ++i){
        int num = i;
        if(num == 0 && 2 == 0){
            count++;
        }
        while(num > 0){
            if(num % 10 == 2){
                count++;
            }
            num /=10;
        }
    }
    cout << count;
}