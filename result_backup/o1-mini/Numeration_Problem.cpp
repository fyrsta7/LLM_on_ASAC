#include <iostream>

using namespace std;

int main(){
    int n, x;
    cin >> n >> x;
    int count = 0;
    for(int i=1;i<=n;i++){
        int num = i;
        if(num == 0 && x == 0){
            count++;
        }
        while(num > 0){
            if(num % 10 == x){
                count++;
            }
            num /=10;
        }
    }
    cout << count;
}