#include "MarshalPost.h"
#include "EventNotice.h"
#include <iostream>

MarshalPost::MarshalPost(const std::string& name): EventComponent(name), m_currentFlag("green"), m_operational(true), m_incidentCount(0) {}

MarshalPost::~MarshalPost() {}

void MarshalPost::open() {
    m_operational = true;
    m_currentFlag = "green";
    std::cout << m_name << " clears to green.\n";
}

void MarshalPost::close() {
    m_operational = false;
    m_currentFlag = "red";
    std::cout << m_name << " holds red flag.\n";
}

void MarshalPost::reportStatus() const {
    std::cout << "[MarshalPost] " << m_name << " flag=" << m_currentFlag<< " operational=" << (m_operational ? "yes" : "no") << "\n";
}

int MarshalPost::getCapacity() const { return 0; } //marshal posts hold no spectators

void MarshalPost::update(const EventNotice& notice) {
    const std::string& type = notice.getType();
    if (type == "RED_FLAG") {
        m_currentFlag = "red"; m_operational = false;
        std::cout << "  -> " << m_name << " displays RED, session stopped\n";
        // Specs 4.4 extra feature: incident-count escalation
        m_incidentCount++;
        if (m_incidentCount >= REINFORCEMENT_THRESHOLD) {
            std::cout << "  -> " << m_name << " has handled " << m_incidentCount << " incidents, REQUESTING REINFORCEMENT\n";
        }
    } else if (type == "YELLOW_FLAG") {
        m_currentFlag = "yellow";
        std::cout << "  -> " << m_name << " displays YELLOW, caution only\n";
    } else if (type == "RESUME") {
        m_currentFlag = "green"; m_operational = true;
        std::cout << "  -> " << m_name << " clears to GREEN\n";
    } else if (type == "WEATHER_ALERT") {
        // Specs 4.4 extra feature: if weather is too severe, flag to red
        if (notice.getSeverity() >= 4) {
            m_currentFlag = "red"; m_operational = false;
            std::cout << "  -> " << m_name << " auto-escalates to RED (severe weather)\n";
        } else {
            std::cout << "  -> " << m_name << " monitors conditions, no escalation\n";
        }
    }
}
