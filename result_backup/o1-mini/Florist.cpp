#include <iostream>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    if(n ==0){
        cout<<0;
        return 0;
    }
    long long h;
    cin >> h;
    // Condition A: peaks at even positions
    int countA =1;
    long long lastA = h;
    bool expectPeakA = true;
    // Condition B: valleys at even positions
    int countB =1;
    long long lastB = h;
    bool expectValleyB = true;
    for(int i=1;i<n;i++){
        cin >> h;
        // For Condition A
        if(expectPeakA){
            if(h > lastA){
                countA++;
                lastA = h;
                expectPeakA = false;
            }
        }
        else{
            countA++;
            lastA = h;
            expectPeakA = true;
        }
        // For Condition B
        if(expectValleyB){
            if(h < lastB){
                countB++;
                lastB = h;
                expectValleyB = false;
            }
        }
        else{
            countB++;
            lastB = h;
            expectValleyB = true;
        }
    }
    if(n ==1){
        cout<<1;
        return 0;
    }
    // To ensure condition A and B are met, we need to verify the subsequences
    // So, implement two separate passes
    // Reset and implement strict condition
    // Condition A: peaks at even positions
    // Implement a separate pass for condition A
    // First pass for Condition A
    // Reset input
    cin.clear();
    cin.seekg(0);
    cin >> n;
    cin >> h;
    countA =1;
    lastA = h;
    expectPeakA = true;
    for(int i=1;i<n;i++){
        cin >> h;
        if(expectPeakA){
            if(h > lastA){
                countA++;
                lastA = h;
                expectPeakA = false;
            }
            else{
                lastA = h;
            }
        }
        else{
            countA++;
            lastA = h;
            expectPeakA = true;
        }
    }
    // Second pass for Condition B
    cin.clear();
    cin.seekg(0);
    cin >> n;
    cin >> h;
    countB =1;
    lastB = h;
    expectValleyB = true;
    for(int i=1;i<n;i++){
        cin >> h;
        if(expectValleyB){
            if(h < lastB){
                countB++;
                lastB = h;
                expectValleyB = false;
            }
            else{
                lastB = h;
            }
        }
        else{
            countB++;
            lastB = h;
            expectValleyB = true;
        }
    }
    cout << (countA > countB ? countA : countB);
}