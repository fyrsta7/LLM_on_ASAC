#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int M, S, T;
    cin >> M >> S >> T;
    
    int distance = 0;
    for (int time = 1; time <= T; ++time) {
        if (M >= 10) {
            // Use the flash spell
            distance += 60;
            M -= 10;
        } else {
            // Compare distance by either running or waiting to regenerate mana
            int distance_if_run = distance + 17;
            int distance_if_wait = distance + min(T - time, (10 - M + 3) / 4 * 60);  // If waits and then flashes
            if(distance_if_run >= S || distance_if_wait >= S) {
                distance = max(distance_if_run, distance_if_wait);
                if(distance >= S) {
                    cout << "Yes" << endl;
                    cout << time << endl;
                    return 0;
                }
            } else {
                distance = distance_if_run;
            }
            M = min(1000, M + 4); // Regenerate mana
        }
    }
    
    if (distance >= S) {
        cout << "Yes" << endl;
        cout << T << endl;
    } else {
        cout << "No" << endl;
        cout << distance << endl;
    }
    
    return 0;
}