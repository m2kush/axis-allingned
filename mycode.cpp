#include <bits/stdc++.h>
using namespace std;

// Building teen chizo se bani hai x coordinate, y coordinate and weight of the building
struct Building{
    int x,y,w;
};

// comparision function to check the x coordinates of two buildings
bool comparisonX(const Building &a, const Building &b){
    return a.x < b.x;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N,K;
    cin >> N >> K;
    vector<Building> buildings(N);
    for(int i=0;i<N;i++)
        cin >> buildings[i].x >> buildings[i].y >> buildings[i].w;
    sort(buildings.begin(), buildings.end(), comparisonX);

    long long bestCost = LLONG_MAX;
    vector<double> bestRect(4);

    // For sliding window left→right:
    for(int left = 0; left < N; ++left){
        multiset<pair<int,int>> low, high; // (w,y)
        multiset<int> ys_low;
        long long sumLow = 0;

        auto rebalance = [&](){
            while((int)low.size() > K){
                auto it = prev(low.end());
                sumLow -= it->first;
                ys_low.erase(ys_low.find(it->second));
                high.insert(*it);
                low.erase(it);
            }
            while((int)low.size() < K && !high.empty()){
                auto it = high.begin();
                sumLow += it->first;
                ys_low.insert(it->second);
                low.insert(*it);
                high.erase(it);
            }
            if(!low.empty() && !high.empty() && low.rbegin()->first > high.begin()->first){
                auto itL = prev(low.end());
                auto itH = high.begin();
                sumLow += itH->first - itL->first;
                ys_low.erase(ys_low.find(itL->second));
                ys_low.insert(itH->second);
                low.insert(*itH);
                high.insert(*itL);
                low.erase(itL);
                high.erase(itH);
            }
        };

        for(int right = left; right < N; ++right){
            // ekine insert
            low.insert({buildings[right].w, buildings[right].y});
            sumLow += buildings[right].w;
            ys_low.insert(buildings[right].y);
            rebalance();

            if((int)low.size() == K){
                // get y-window min/max in O(log K)
                double y1 = *ys_low.begin();
                double y2 = *prev(ys_low.end());

                double x1 = buildings[left].x;
                double x2 = buildings[right].x;
                double perimeter = 2.0 * (abs(x2-x1) + abs(y2-y1));
                double cost = perimeter + sumLow;

                if(cost < bestCost){
                    bestCost = cost;
                    bestRect = {x1, y1, x2, y2};
                }
            }
        }
    }

    // Output
    cout << fixed << setprecision(6) << bestCost << '\n';
    double x1 = bestRect[0], y1 = bestRect[1];
    double x2 = bestRect[2], y2 = bestRect[3];
    cout << x1<<' '<<y1<<' '<<x2<<' '<<y1<<'\n';
    cout << x2<<' '<<y1<<' '<<x2<<' '<<y2<<'\n';
    cout << x2<<' '<<y2<<' '<<x1<<' '<<y2<<'\n';
    cout << x1<<' '<<y2<<' '<<x1<<' '<<y1<<'\n';
    return 0;
}
