#include <iostream>

using namespace std;

int main() {
    int n, m, x;
    long long k;
    cin >> n >> m >> k >> x;
    
    // Calculate the number of moves taking the remainder by n
    long long position = (x + (k * m) % n) % n;
    
    cout << position << endl;

    return 0;
}