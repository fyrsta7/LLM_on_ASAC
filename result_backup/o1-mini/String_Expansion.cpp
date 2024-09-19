#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

int main(){
    int p1, p2, p3;
    cin >> p1 >> p2 >> p3;
    string s;
    cin >> s;
    string res = "";
    int n = s.length();
    for(int i=0;i<n;i++){
        if(s[i]=='-' && i>0 && i<n-1){
            char left = s[i-1];
            char right = s[i+1];
            bool left_is_lower = islower(left);
            bool left_is_digit = isdigit(left);
            bool right_is_lower = islower(right);
            bool right_is_digit = isdigit(right);
            if( ((left_is_lower && right_is_lower) || (left_is_digit && right_is_digit)) && right > left){
                if(right == left +1){
                    // Remove '-', just continue
                    // Remove the '-' by not adding it to res
                }
                else{
                    // Expand
                    string fillers = "";
                    for(char c = left +1; c < right; c++) fillers += c;
                    if(p3 == 2){
                        reverse(fillers.begin(), fillers.end());
                    }
                    for(char c: fillers){
                        if(p1 ==3){
                            res += string(p2, '*');
                        }
                        else{
                            if(isdigit(c)){
                                res += string(p2, c);
                            }
                            else if(islower(c)){
                                if(p1 ==1){
                                    res += string(p2, c);
                                }
                                else if(p1 ==2){
                                    res += string(p2, toupper(c));
                                }
                            }
                        }
                    }
                }
                continue;
            }
        }
        res += s[i];
    }
    cout << res;
}