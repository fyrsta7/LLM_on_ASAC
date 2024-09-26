#include <bits/stdc++.h>
using namespace std;

int main(){
    string isbn;
    cin >> isbn;
    auto convert_str = [&](char c) -> int {
        if(c >= '0' && c <= '9') return c - '0';
        if(c == 'X') return 10;
        return -1;
    };
    // str_list indexed from 0 to 10
    string str_list = "0123456789X";
    // Compute sum
    // Positions: 1,3,4,5,7,8,9,10,11 in 0-based: 0,2,3,4,6,7,8,9,10
    int sum = 0;
    int weights[] = {1,2,3,4,5,6,7,8,9};
    int indices[] = {0,2,3,4,6,7,8,9,10};
    for(int i=0;i<9;i++) {
        int val = convert_str(isbn[indices[i]]);
        if(val == -1){
            // Invalid character, handle as per problem constraints
            // Assuming to treat invalid as -1 which will not match any checksum
            val = -1;
        }
        sum += val * weights[i];
    }
    int answer = sum % 11;
    // Get expected last character
    char last_num;
    if(answer >=0 && answer <=10){
        last_num = str_list[answer];
    }
    else{
        last_num = '0'; // default, though answer should be 0..10
    }
    int last_val = convert_str(isbn[12]);
    bool right = (last_val == answer);
    if(right){
        cout << "Right";
    }
    else{
        string corrected = isbn.substr(0,12) + last_num;
        cout << corrected;
    }
}