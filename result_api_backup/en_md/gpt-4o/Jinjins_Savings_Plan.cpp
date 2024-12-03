#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream infile("save.in");
    ofstream outfile("save.out");

    int budget[12];
    for (int i = 0; i < 12; ++i) {
        infile >> budget[i];
    }

    int balance = 0;
    int saved = 0;

    for (int month = 0; month < 12; ++month) {
        balance += 300;  // Mom gives 300 at the beginning of each month
        
        if (balance < budget[month]) {
            outfile << -(month + 1) << endl;  // output the 1-based month
            return 0;  // exit the program
        }

        balance -= budget[month];  // spend the budget

        if (balance >= 100) {
            int deposit = (balance / 100) * 100;
            saved += deposit;
            balance -= deposit;
        }
    }

    int final_amount = balance + saved + (saved / 5);  // balance + saved + 20% interest
    outfile << final_amount << endl;

    return 0;
}