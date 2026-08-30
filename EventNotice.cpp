#include "EventNotice.h"

EventNotice::EventNotice(const std::string& type, const std::string& sector, const std::string& message, int severity)
: m_type(type), m_sector(sector), m_message(message), m_severity(severity) {}

const std::string& EventNotice::getType() const { return m_type; }
const std::string& EventNotice::getSector() const { return m_sector; }
const std::string& EventNotice::getMessage() const { return m_message; }
int EventNotice::getSeverity() const { return m_severity; }

std::string EventNotice::toString() const {
    return "[" + m_type + "] " + (m_sector.empty() ? "(all sectors) " : m_sector + " ") + m_message;
}
