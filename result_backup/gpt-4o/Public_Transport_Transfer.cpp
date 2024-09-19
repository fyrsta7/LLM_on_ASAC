#include <iostream>
#include <queue>

using namespace std;

struct Ticket {
    int price;
    int time;
};

int main() {
    int n;
    cin >> n;
    
    priority_queue<Ticket, vector<Ticket>, greater<>> tickets;
    int total_cost = 0;
    
    for (int i = 0; i < n; ++i) {
        int type, price, time;
        cin >> type >> price >> time;
        
        if (type == 0) {
            tickets.push({price, time});
            total_cost += price;
        } else {
            while (!tickets.empty() && (time - tickets.top().time > 45)) {
                tickets.pop();
            }

            if (!tickets.empty() && price <= tickets.top().price) {
                tickets.pop();
            } else {
                total_cost += price;
            }
        }
    }
    
    cout << total_cost << endl;
    
    return 0;
}