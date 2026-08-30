#include "MedicalStation.h"
#include "EventNotice.h"
#include <iostream>

MedicalStation::MedicalStation(const std::string& name) : EventComponent(name), m_readiness("standby") {}

MedicalStation::~MedicalStation() {}

void MedicalStation::open() { m_readiness = "standby"; std::cout << m_name << " on standby.\n"; }
void MedicalStation::close() { /* medical never fully closes */ std::cout << m_name << " remains reachable.\n"; }

void MedicalStation::reportStatus() const {
    std::cout << "[MedicalStation] " << m_name << " readiness=" << m_readiness << "\n";
}

int MedicalStation::getCapacity() const { return 0; }

void MedicalStation::update(const EventNotice& notice) {
    const std::string& type = notice.getType();
    if (type == "RED_FLAG" || type == "MEDICAL_INCIDENT" || type == "EVACUATE") {
        m_readiness = "deployed";
        std::cout << "  -> " << m_name << " escalates to DEPLOYED\n";
    } else if (type == "RESUME") {
        m_readiness = "standby";
        std::cout << "  -> " << m_name << " returns to STANDBY\n";
    } else {
        std::cout << "  -> " << m_name << " remains operational, no action needed\n";
    }
}