#include <iostream>
using namespace std;

int main() {
    long long n, m, k, x;
    cin >> n >> m >> k >> x;
    
    // Calculate the total effective number of moves
    long long effective_moves = (long long)pow(10, k) % n; // 10^k % n to minimize computation
    long long position = (x - 1 + effective_moves) % n; // player x's position after the moves
    
    // Calculate the final position based on the defined movement
    int final_position = (position + m) % n;
    
    cout << final_position << endl;
    return 0;
}