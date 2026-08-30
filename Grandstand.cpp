#include "Grandstand.h"
#include "EventNotice.h"
#include <iostream>

Grandstand::Grandstand(const std::string& name, int capacity) : EventComponent(name), m_open(true), m_capacity(capacity), m_occupancy(0) {}

Grandstand::~Grandstand() {}

void Grandstand::open() { m_open = true; std::cout << m_name << " opens to spectators.\n"; }
void Grandstand::close() { m_open = false; std::cout << m_name << " closes.\n"; }

void Grandstand::reportStatus() const {
    std::cout << "[Grandstand] " << m_name << " open=" << (m_open ? "yes" : "no") << " occupancy=" << m_occupancy << "/" << m_capacity << "\n";
}

int Grandstand::getCapacity() const { return m_capacity; }

void Grandstand::setOccupancy(int count) { m_occupancy = count; }

void Grandstand::update(const EventNotice& notice) {
    const std::string& type = notice.getType();
    if (type == "EVACUATE") {
        m_open = false;
        std::cout << "  -> " << m_name << " evacuates spectators\n";
    } else if (type == "CAPACITY_ALERT") {
        // condition-based decision: "if occupancy ratio >= threshold". 
        // This is the branch that will appear as an alt
        // fragment with guards in SD3.
        double ratio = m_capacity > 0 ? static_cast<double>(m_occupancy) / m_capacity : 0.0;
        if (ratio >= CAPACITY_THRESHOLD) {
            std::cout << "  -> " << m_name << " at/above " << (CAPACITY_THRESHOLD * 100) << "% capacity (" << m_occupancy << "/" << m_capacity << "), holding entry\n";
        } else {
            std::cout << "  -> " << m_name << " below the capacity threshold (" << m_occupancy << "/" << m_capacity << "), no action\n";
        }
    } else if (type == "RESUME") {
        m_open = true;
        std::cout << "  -> " << m_name << " reopens\n";
    } else if (type == "YELLOW_FLAG" || type == "WEATHER_ALERT") {
        std::cout << "  -> " << m_name << " stays open (under cover)\n";
    }
}
