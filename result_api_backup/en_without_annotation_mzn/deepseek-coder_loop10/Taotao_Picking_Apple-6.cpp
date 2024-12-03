#include <iostream>
using namespace std;

int main() {
    int apple[10], h, num = 0;
    for (int i = 0; i < 10; ++i) cin >> apple[i];
    cin >> h;
    for (int i = 0; i < 10; ++i) {
        if (apple[i] <= h + 30) ++num;
    }
    cout << num << endl;
    return 0;
}