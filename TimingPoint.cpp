#include "TimingPoint.h"
#include "EventNotice.h"
#include <iostream>

TimingPoint::TimingPoint(const std::string& name) : EventComponent(name), m_timingActive(true), m_lapsRecorded(0), m_bestLapSeconds(-1.0) {}

TimingPoint::~TimingPoint() {}

void TimingPoint::open() { m_timingActive = true; std::cout << m_name << " timing resumed.\n"; }
void TimingPoint::close() { m_timingActive = false; std::cout << m_name << " timing frozen.\n"; }

void TimingPoint::reportStatus() const {
    std::cout << "[TimingPoint] " << m_name << " active=" << (m_timingActive ? "yes" : "no")<< " lapsRecorded=" << m_lapsRecorded << "\n";
}

int TimingPoint::getCapacity() const { return 0; }

void TimingPoint::update(const EventNotice& notice) {
    const std::string& type = notice.getType();
    if (type == "RED_FLAG") {
        m_timingActive = false;
        std::cout << "  -> " << m_name << " freezes lap times\n";
    } else if (type == "RESUME") {
        m_timingActive = true;
        std::cout << "  -> " << m_name << " resumes timing\n";
    }
}

void TimingPoint::recordLap(double lapSeconds) {
    if (!m_timingActive) {
        std::cout << "  -> " << m_name << " ignores lap time, timing is frozen\n";
        return;
    }
    m_lapsRecorded++;
    if (m_bestLapSeconds < 0.0 || lapSeconds < m_bestLapSeconds) {
        m_bestLapSeconds = lapSeconds;
        std::cout << "  -> " << m_name << " NEW BEST LAP: " << lapSeconds << "s\n";
    } else {
        std::cout << "  -> " << m_name << " lap recorded: " << lapSeconds << "s (best remains " << m_bestLapSeconds << "s)\n";
    }
}
