#include<iostream>
#include<map>

using namespace std;

int main()
{
    int N;
    cin >> N;
    map<int, long long> travelTimeById;
    for (int i = 0; i < N; i++) {
        int day, hour, minute, id;
        char status;
        cin >> day >> hour >> minute >> id >> status;
        int timeInMin = (day * 24 + hour) * 60 + minute;
        if (status == 'A') travelTimeById[id] -= timeInMin;
        if (status == 'C' || status == 'S') travelTimeById[id] += timeInMin;
    }
    for (auto& time : travelTimeById) {
        cout << time.second << ' ';
    }
    cout << endl;
    return 0;
}
