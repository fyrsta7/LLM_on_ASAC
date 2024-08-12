#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Record {
    int type; // 0 for subway, 1 for bus
    int price;
    int time;
};

int main() {
    int n;
    cin >> n;
    vector<Record> records(n);
    
    for (int i = 0; i < n; i++) {
        cin >> records[i].type >> records[i].price >> records[i].time;
    }
    
    int totalCost = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> ticketQueue; // (time, price)
    
    for (const auto& record : records) {
        if (record.type == 0) {
            // Subway ride
            ticketQueue.push({record.time + 45, record.price});
            totalCost += record.price;
        } else {
            // Bus ride
            while (!ticketQueue.empty() && ticketQueue.top().first < record.time) {
                ticketQueue.pop(); // Remove expired tickets
            }
            bool usedTicket = false;
            if (!ticketQueue.empty()) {
                auto ticket = ticketQueue.top();
                if (ticket.second >= record.price) {
                    ticketQueue.pop(); // Use the ticket
                    usedTicket = true;
                }
            }
            if (!usedTicket) {
                totalCost += record.price;
            }
        }
    }
    
    cout << totalCost << endl;
    return 0;
}