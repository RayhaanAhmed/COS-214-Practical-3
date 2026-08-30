#include "EventGroup.h"
#include "EventNotice.h"
#include <algorithm>
#include <iostream>

void EventGroup::add(EventComponent* c)
{
    if (!c) return;
    m_children.push_back(c);
    Observer* obs = dynamic_cast<Observer*>(c);
    if (obs) {
        attach(obs);
    }
}

void EventGroup::remove(EventComponent* c)
{
    for (auto it = m_children.begin(); it != m_children.end(); ++it) {
        if (*it == c)
        {
            m_children.erase(it);
            Observer* obs = dynamic_cast<Observer*>(c);
            if (obs) {
                detach(obs);
            }
            return;
        }
    }
}

EventGroup::~EventGroup() {
    for (EventComponent* c : m_children) {
        delete c;
    }
    m_children.clear();
}

void EventGroup::open() {
    std::cout << m_name << " opening.\n";
    for (EventComponent* c : m_children) {
        c->open();
    }
}

void EventGroup::close() {
    std::cout << m_name << " closing.\n";
    for (EventComponent* c : m_children) {
        c->close();
    }
}

void EventGroup::reportStatus() const {
    std::cout << "[EventGroup] " << m_name << " (" << m_children.size() << " children)\n";
    for (EventComponent* c : m_children) {
        c->reportStatus();
    }
}

int EventGroup::getCapacity() const {
    int total = 0;
    for (EventComponent* c : m_children) {
        total += c->getCapacity();
    }
    return total;
}

// condition-based decision (alt/opt guard)
// [occupancy >= capacity] -> self-issue CAPACITY_ALERT to this group's children
// [else] -> no action
void EventGroup::checkCapacityThreshold(int currentOccupancy) {
    int cap = getCapacity();
    if (cap > 0 && currentOccupancy >= cap) {
        std::cout << m_name << ": capacity threshold reached (" << currentOccupancy << "/" << cap << "), self-issuing CAPACITY_ALERT\n";
        EventNotice alert("CAPACITY_ALERT", m_name, "at or above capacity", 4);
        notify(alert); // Subject role: cascade to this group's own observers
    } else {
        std::cout << m_name << ": occupancy " << currentOccupancy << "/" << cap << ", below threshold, no action\n";
    }
}

void EventGroup::update(const EventNotice& notice) {
    std::cout << m_name << " received " << notice.toString() << ", cascading to children\n";
    notify(notice); // Subject role: forward to this group's own observers
}
