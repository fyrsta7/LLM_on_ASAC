#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> apple(10);
    int h;
    
    // Input the values of the array apple
    for(int i = 0; i < 10; ++i) {
        cin >> apple[i];
    }
    
    // Input the value of h
    cin >> h;

    int num = 0;
    
    // Counting the number of apples within the height of h + 30
    for(int i = 0; i < 10; ++i) {
        if(apple[i] <= h + 30) {
            ++num;
        }
    }
    
    // Output the result
    cout << num << endl;
    
    return 0;
}