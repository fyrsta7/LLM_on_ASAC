#include <iostream>
#include <deque>
using namespace std;

struct Ticket {
    int t_subway;
    int subway_fare;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    long long total_cost = 0;
    deque<Ticket> tickets;
    for(int i=0;i<n;i++){
        int mode, price, ti;
        cin >> mode >> price >> ti;
        if(mode == 0){
            total_cost += price;
            tickets.push_back(Ticket{ti, price});
        }
        else{
            // Remove expired tickets
            while(!tickets.empty() && ti - tickets.front().t_subway > 45){
                tickets.pop_front();
            }
            // Find the earliest valid ticket with subway_fare >= bus fare
            bool used = false;
            for(auto it = tickets.begin(); it != tickets.end(); ++it){
                if(it->subway_fare >= price){
                    tickets.erase(it);
                    used = true;
                    break;
                }
            }
            if(!used){
                total_cost += price;
            }
        }
    }
    cout << total_cost;
}