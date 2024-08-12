#include <fstream>
using namespace std;

int main() {
    ifstream fin("save.in");
    ofstream fout("save.out");
    
    int budget[12];
    for (int i = 0; i < 12; ++i) {
        fin >> budget[i];
    }
    
    int savings = 0;
    int cash = 0;
    
    for (int i = 0; i < 12; ++i) {
        cash += 300;
        if (cash < budget[i]) {
            fout << -(i + 1) << endl;
            return 0;
        }
        int deposit = ((cash - budget[i]) / 100) * 100;
        if (deposit > 0) {
            savings += deposit;
            cash -= deposit;
        }
        cash -= budget[i];
    }
    
    fout << cash + (savings * 1.2) << endl;
    return 0;
}