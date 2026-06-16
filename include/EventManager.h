#pragma once
#include <vector>
#include "Event.h"

class EventManager {
private:
    std::vector<Event> events;
    void loadEvents();
public:
    EventManager();
    const Event& getEvent(int eventId) const;
    int getTotalEvents() const;
};
