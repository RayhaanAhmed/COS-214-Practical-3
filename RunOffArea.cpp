#include "RunOffArea.h"
#include "EventNotice.h"
#include <iostream>

RunOffArea::RunOffArea(const std::string& name) : EventComponent(name), m_clear(true) {}
RunOffArea::~RunOffArea() {}

void RunOffArea::open() { m_clear = true; std::cout << m_name << " line reopened.\n"; }
void RunOffArea::close() { m_clear = false; std::cout << m_name << " line closed.\n"; }

void RunOffArea::reportStatus() const {
    std::cout << "[RunOffArea] " << m_name << " clear=" << (m_clear ? "yes" : "no") << "\n";
}

int RunOffArea::getCapacity() const { return 0; }

void RunOffArea::update(const EventNotice& notice) {
    const std::string& type = notice.getType();
    if (type == "RED_FLAG") {
        m_clear = false;
        std::cout << "  -> " << m_name << " closed, marshals cleaning track\n";
    } else if (type == "RESUME") {
        m_clear = true;
        std::cout << "  -> " << m_name << " reopened, stay safe\n";
    }
}
