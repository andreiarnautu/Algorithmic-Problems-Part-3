/**
  *  Worg
  */
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

struct Event {
    int start, end, id;

    Event() {}

    Event(int _start, int _end, int _id) : start(_start), end(_end), id(_id){

    }

    bool operator <(const Event& other) const {
        if (start != other.start) {
            return start < other.start;
        } else if (end != other.end) {
            return end < other.end;
        }
        return id < other.id;
    }
};

int main() {
    int n; std::cin >> n;
    std::vector<Event> events(n);
    std::vector<int> answer(n + 1);
    for (int i = 0; i < n; i++) {
        std::cin >> events[i].start >> events[i].end;
        events[i].id = i + 1;
    }
    std::sort(events.begin(), events.end());

    int step = 1;
    std::set<Event> active_events;
    for (int i = 0; i < n || !active_events.empty(); ) {
        if (i == n || (step < events[i].start && !active_events.empty())) {
            answer[active_events.begin()->id] = step;
            active_events.erase(active_events.begin());
            step += 1;
        } else {
            step = std::max(step, events[i].start);
            while (i < n && events[i].start <= step) {
                active_events.emplace(events[i].end, events[i].start, events[i].id);
                i += 1;
            }
         }
    }

    for (int i = 1; i <= n; i++) {
        std::cout << answer[i] << " ";
    }
    std::cout << '\n';

    return 0;
}
