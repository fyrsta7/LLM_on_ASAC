#include <iostream>
#include <vector>
using namespace std;

const vector<int> matchsticks = {6,2,5,5,4,5,6,3,7,6}; // matchsticks needed for digits 0-9

int main() {
    int n;
    cin >> n;
    
    int result = 0;
    
    // Check all possible values of A and B to find number of valid equations
    for (int A = 0; A < 1000; ++A) {
        int matchsticks_A = 0, temp_A = A;
        // Determine matchsticks used by A
        if (A == 0) {
            matchsticks_A = matchsticks[0];
        } else {
            while (temp_A > 0) {
                matchsticks_A += matchsticks[temp_A % 10];
                temp_A /= 10;
            }
        }
        
        for (int B = 0; B < 1000; ++B) {
            int matchsticks_B = 0, temp_B = B;
            // Determine matchsticks used by B
            if (B == 0) {
                matchsticks_B = matchsticks[0];
            } else {
                while (temp_B > 0) {
                    matchsticks_B += matchsticks[temp_B % 10];
                    temp_B /= 10;
                }
            }
            
            int C = A + B;
            int matchsticks_C = 0, temp_C = C;
            // Determine matchsticks used by C
            if (C == 0) {
                matchsticks_C = matchsticks[0];
            } else {
                while (temp_C > 0) {
                    matchsticks_C += matchsticks[temp_C % 10];
                    temp_C /= 10;
                }
            }
            
            if (matchsticks_A + matchsticks_B + matchsticks_C + 4 == n) {
                ++result;
            }
        }
    }
    
    cout << result << endl;
    
    return 0;
}