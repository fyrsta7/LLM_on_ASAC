#include <iostream>
using namespace std;

int main() {
    int M, S, T;
    cin >> M >> S >> T;

    int run_distance = 0;
    int flash_distance = 0;
    int mana = M;
    int time = 0;

    while (time < T) {
        if (mana >= 10) {
            flash_distance += 60;
            mana -= 10;
            time++;
        } else {
            int remaining_time = T - time;
            int required_time_to_charge = (10 - mana + 3) / 4;
            if (required_time_to_charge <= remaining_time) {
                time += required_time_to_charge;
                mana += required_time_to_charge * 4;
            } else {
                run_distance += 17 * remaining_time;
                time = T;
                break;
            }
        }
        if (flash_distance >= S) {
            cout << "Yes" << endl;
            cout << time << endl;
            return 0;
        }
        run_distance = max(run_distance, flash_distance);
    }

    run_distance += 17 * (T - time);
    cout << "No" << endl;
    cout << max(run_distance, flash_distance) << endl;
    return 0;
}
