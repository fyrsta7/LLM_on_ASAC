#include <iostream>
using namespace std;

int countOccurrences(int n, int x) {
    int count = 0;
    for (int i = 1; i <= n; ++i) {
        int num = i;
        while (num > 0) {
            if (num % 10 == x) {
                count++;
            }
            num /= 10;
        }
    }
    return count;
}

int main() {
    int n, x;
    cin >> n >> x;
    cout << countOccurrences(n, x) << endl;
    return 0;
}