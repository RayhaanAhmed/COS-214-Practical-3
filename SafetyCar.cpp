#include "SafetyCar.h"
#include "EventNotice.h"
#include <iostream>

SafetyCar::SafetyCar(const std::string& name) : EventComponent(name), m_status("in pit") {}
SafetyCar::~SafetyCar() {}

void SafetyCar::open() { m_status = "in pit"; std::cout << m_name << " ready in pit lane.\n"; }
void SafetyCar::close() { m_status = "deployed"; std::cout << m_name << " deployed.\n"; }

void SafetyCar::reportStatus() const {
    std::cout << "[SafetyCar] " << m_name << " status=" << m_status << "\n";
}

int SafetyCar::getCapacity() const { return 0; }

void SafetyCar::update(const EventNotice& notice) {
    const std::string& type = notice.getType();
    if (type == "RED_FLAG" || type == "MEDICAL_INCIDENT") {
        m_status = "deployed";
        std::cout << "  -> " << m_name << " deploys to lead the field\n";
    } else if (type == "RESUME") {
        m_status = "in pit";
        std::cout << "  -> " << m_name << " returns to pit lane\n";
    }
}
