#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> apple = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // Example values
    int h = 50; // Example value
    int num = 0;

    for (int i = 0; i < 10; ++i) {
        if (apple[i] <= h + 30) {
            ++num;
        }
    }

    cout << num << endl;
    return 0;
}