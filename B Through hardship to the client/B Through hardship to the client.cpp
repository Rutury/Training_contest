#include <iostream>
#include <map>

using namespace std;

class Event {
public:
    int day;
    int hour;
    int minute;
    int id;
    char status;

    Event() {
        day = -1;
        hour = -1;
        minute = -1;
        id = -1;
        status = '0';
    }

    void read_from_console() { cin >> day >> hour >> minute >> id >> status; }

    int time_into_minutes() const { return (day * 24 + hour) * 60 + minute; }
};

int main()
{
    map<int, long long int> rockets;
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        Event event;
        event.read_from_console();
        if (rockets.count(event.id) == 0) {
            rockets[event.id] = 0;
        }
        if (event.status == 'A') {
            rockets[event.id] -= event.time_into_minutes();
        }
        else if (event.status == 'C' or event.status == 'S') {
            rockets[event.id] += event.time_into_minutes();
        }
    }
    for (auto& rocket : rockets) {
        cout << rocket.second << ' ';
    }
}
