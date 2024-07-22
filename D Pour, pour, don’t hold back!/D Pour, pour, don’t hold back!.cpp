#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>

using namespace std;

class TOrder {
public:
    int start;
    int end;
    int cost;

    TOrder(int start, int end, int cost) : start(start), end(end), cost(cost) {}

    int Duration() const { return end - start; }
};

class TOrders {
public:
    vector<TOrder> orders;
    map<int, unordered_set<int>> ordersByStart;
    map<int, unordered_set<int>> ordersByEnd;
    map<int, long long> totalCostStartsBefore;
    map<int, long long> totalDurationEndsBefore;

    void addOrder(int start, int end, int cost) {
        orders.emplace_back(start, end, cost);
        ordersByStart[start].insert(orders.size() - 1);
        ordersByEnd[end].insert(orders.size() - 1);
    }

    void updateTotalCost() {
        long long sum = 0;
        totalCostStartsBefore[0] = 0;
        for (auto& idxSet : ordersByStart) {
            for (int idx : idxSet.second)
                sum += orders[idx].cost;
            totalCostStartsBefore[idxSet.first] = sum;
        }
    }

    void updateTotalDuration() {
        long long sum = 0;
        totalDurationEndsBefore[0] = sum;
        for (auto& idxSet : ordersByEnd) {
            for (int idx : idxSet.second)
                sum += orders[idx].Duration();
            totalDurationEndsBefore[idxSet.first] = sum;
        }
    }
    
    long long totalCostStartsWithin(int start, int end) const {
        long long startSum, endSum;
        auto itr = totalCostStartsBefore.lower_bound(start);
        itr--;
        startSum = itr->second;
        itr = totalCostStartsBefore.upper_bound(end);
        itr--;
        endSum = itr->second;
        return endSum - startSum;
    }

    long long totalDurationEndsWithin(int start, int end) const {
        long long startSum, endSum;
        auto itr = totalDurationEndsBefore.lower_bound(start);
        itr--;
        startSum = itr->second;
        itr = totalDurationEndsBefore.upper_bound(end);
        itr--;
        endSum = itr->second;
        return endSum - startSum;
    }
};

int main()
{
    int N;
    cin >> N;
    TOrders orders;
    for (int i = 0; i < N; i++) {
        int start, end, cost;
        cin >> start >> end >> cost;
        orders.addOrder(start, end, cost);
    }
    orders.updateTotalCost();
    orders.updateTotalDuration();
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int start, end, type;
        cin >> start >> end >> type;
        if (type == 1) cout << orders.totalCostStartsWithin(start, end) << ' ';
        else if (type == 2) cout << orders.totalDurationEndsWithin(start, end) << ' ';
    }
    cout << endl;
}
