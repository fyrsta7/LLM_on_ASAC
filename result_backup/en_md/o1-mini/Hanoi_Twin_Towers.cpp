#include <iostream>
#include <string>
using namespace std;

int main(){
    int n;
    cin>>n;
    string num = "1";
    for(int i=0;i<n+1;i++){
        // multiply num by 2
        int carry=0;
        for(int j=num.size()-1;j>=0;j--){
            int temp = (num[j]-'0') *2 + carry;
            num[j]= (temp%10)+'0';
            carry = temp /10;
        }
        if(carry){
            num = to_string(carry) + num;
        }
    }
    // subtract 2
    int i_pos = num.size()-1;
    int borrow=2;
    while(i_pos>=0 && borrow >0){
        int digit = num[i_pos]-'0';
        if(digit >= borrow){
            num[i_pos] = (digit - borrow) + '0';
            borrow=0;
        }
        else{
            num[i_pos] = (digit +10 - borrow) + '0';
            borrow=1;
        }
        i_pos--;
    }
    // remove leading zeros
    while(num.size()>1 && num[0]=='0') num.erase(0,1);
    cout<<num;
}