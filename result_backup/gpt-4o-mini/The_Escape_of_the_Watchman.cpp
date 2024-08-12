#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int M, S, T;
    cin >> M >> S >> T;

    const int run_speed = 17;
    const int flash_distance = 60;
    const int flash_cost = 10;
    const int mana_regen = 4;

    // Calculate maximum distance by running
    int max_distance_by_running = run_speed * T;

    // Calculate maximum flash uses and remaining mana
    int max_flashes = M / flash_cost;  // Number of times he can flash
    int total_regen_time = max(0, T - (max_flashes * 10 / mana_regen));  // Time spent regenerating mana
    M += total_regen_time * mana_regen;  // Regenerate mana during rest
    max_flashes = M / flash_cost;  // Recalculate usable flashes after regeneration

    int flash_distance = max_flashes * flash_distance;
    int total_distance = max_distance_by_running + flash_distance;

    if (total_distance >= S) {
        // Escape is possible, calculate minimum time needed
        int time_needed = 0;

        // Calculate how many flashes are needed
        int flashes_needed = (S - run_speed * T + flash_distance - 1) / flash_distance;
        time_needed += flashes_needed;
        S -= flashes_needed * flash_distance;

        // Calculate remaining time for running
        if (S > 0) {
            time_needed += (S + run_speed - 1) / run_speed;
        }
        
        cout << "Yes" << endl;
        cout << time_needed << endl;
    } else {
        // Escape is not possible
        cout << "No" << endl;
        cout << total_distance << endl;
    }

    return 0;
}