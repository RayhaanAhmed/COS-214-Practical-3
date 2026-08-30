#ifndef EVENTNOTICE_H
#define EVENTNOTICE_H
#include <string>

/**
 * @brief A single notice pushed from a Subject to its Observers.
 * Push style payload: carries everything an Observer needs to react
 * without querying the Subject for further state.
 */
class EventNotice {
private:
    std::string m_type;
    std::string m_sector;
    std::string m_message;
    int m_severity;

public:
    EventNotice(const std::string& type, const std::string& sector, const std::string& message, int severity = 1);
    const std::string& getType() const;
    const std::string& getSector() const;
    const std::string& getMessage() const;
    int getSeverity() const;
    std::string toString() const;
};
#endif
