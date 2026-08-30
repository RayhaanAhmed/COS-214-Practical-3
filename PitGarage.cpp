#include "PitGarage.h"
#include "EventNotice.h"
#include <iostream>

PitGarage::PitGarage(const std::string& name, int capacity) : EventComponent(name), m_laneOpen(true), m_capacity(capacity), m_speedLimited(false) {}

PitGarage::~PitGarage() {}

void PitGarage::open() { m_laneOpen = true; std::cout << m_name << " lane open.\n"; }
void PitGarage::close() { m_laneOpen = false; std::cout << m_name << " lane closed.\n"; }

void PitGarage::reportStatus() const {
    std::cout << "[PitGarage] " << m_name << " laneOpen=" << (m_laneOpen ? "yes" : "no") << " queued=" << m_releaseQueue.size() << " speedLimited=" << (m_speedLimited ? "yes" : "no") << "\n";
}

int PitGarage::getCapacity() const { return m_capacity; }

void PitGarage::enqueueCar(const std::string& car) {
    // Specs 4.4 original feature: Don't let the garage be unbounded
    if (static_cast<int>(m_releaseQueue.size()) >= m_capacity) {  //queue full
        std::cout << "  -> " << m_name << " REJECTS " << car << ", garage at capacity\n";
        return;
    }
    m_releaseQueue.push(car);
}

void PitGarage::update(const EventNotice& notice) {
    const std::string& type = notice.getType();
    if (type == "RED_FLAG") {
        m_laneOpen = false;
        std::cout << "  -> " << m_name << " holds all cars, lane closed\n";
    } else if (type == "PIT_LANE_CLOSED") {
        m_laneOpen = false;
        std::cout << "  -> " << m_name << " pit lane closed\n";
    } else if (type == "RESUME") {
        m_laneOpen = true;
        std::cout << "  -> " << m_name << " releases " << m_releaseQueue.size() << " queued car(s) in order\n";
        while (!m_releaseQueue.empty()) m_releaseQueue.pop();
        if (m_speedLimited) {
            m_speedLimited = false;
            std::cout << "  -> " << m_name << " lifts weather speed limit\n";
        }
    } else if (type == "WEATHER_ALERT") {
        // Impose speed limit with bad conditions
        m_speedLimited = true;
        std::cout << "  -> " << m_name << " imposes pit-lane speed limit (wet conditions)\n";
    }
}
