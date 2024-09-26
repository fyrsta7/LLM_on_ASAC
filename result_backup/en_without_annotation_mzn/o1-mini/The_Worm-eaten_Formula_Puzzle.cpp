#include <bits/stdc++.h>
using namespace std;

int main(){
    int N;
    cin >> N;
    vector<string> add(3);
    for(int i=0;i<3;i++) cin >> add[i];
    // Convert add to add_num
    vector<vector<int>> add_num(3, vector<int>(N));
    for(int i=0;i<3;i++){
        for(int j=0;j<N;j++){
            char c = add[i][j];
            int l = c - 'A';
            if(l <0 || l >=N){
                // Invalid, no solution
                return 0;
            }
            add_num[i][j] = l;
        }
    }
    // Initialize result as 0 to N-1
    vector<int> result(N);
    for(int i=0;i<N;i++) result[i]=i;
    do{
        // Check the addition
        bool valid=true;
        int carry=0;
        for(int j=0;j<N;j++){
            int sum = result[add_num[0][j]] + result[add_num[1][j]] + carry;
            if(sum % N != result[add_num[2][j]]){
                valid=false;
                break;
            }
            carry = sum / N;
        }
        if(valid && carry ==0){
            // Output the result
            for(int i=0;i<N;i++) cout << result[i] << (i<N-1?" ":"\n");
            return 0;
        }
    }while(next_permutation(result.begin(), result.end()));
    return 0;
}