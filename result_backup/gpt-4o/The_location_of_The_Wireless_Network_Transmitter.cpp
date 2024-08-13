#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Intersection {
    int x, y, k;
};

int main() {
    int d, n;
    cin >> d >> n;

    vector<Intersection> intersections(n);
    for (int i = 0; i < n; ++i) {
        cin >> intersections[i].x >> intersections[i].y >> intersections[i].k;
    }

    int max_public_spaces = 0;
    int best_schemes = 0;

    for (int i = 0; i <= 128; ++i) {
        for (int j = 0; j <= 128; ++j) {
            int current_public_spaces = 0;

            for (const auto &intersection : intersections) {
                if (abs(intersection.x - i) <= d && abs(intersection.y - j) <= d) {
                    current_public_spaces += intersection.k;
                }
            }

            if (current_public_spaces > max_public_spaces) {
                max_public_spaces = current_public_spaces;
                best_schemes = 1;
            } else if (current_public_spaces == max_public_spaces) {
                ++best_schemes;
            }
        }
    }

    cout << best_schemes << " " << max_public_spaces << endl;
    return 0;
}