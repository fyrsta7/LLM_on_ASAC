#include <iostream>
using namespace std;

int countTwos(int L, int R) {
    int count = 0;
    for (int i = L; i <= R; i++) {
        int num = i;
        while (num > 0) {
            if (num % 10 == 2) {
                count++;
            }
            num /= 10;
        }
    }
    return count;
}

int main() {
    int L, R;
    cin >> L >> R;
    cout << countTwos(L, R) << endl;
    return 0;
}