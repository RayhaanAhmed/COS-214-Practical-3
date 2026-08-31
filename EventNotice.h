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
/**
     * @brief Constructs a notice.
     * @param type Notice kind, e.g. "RED_FLAG", "CAPACITY_ALERT".
     * @param sector Which area the notice concerns, or "" for all sectors.
     * @param message Human-readable detail shown in reports/logs.
     * @param severity Severity level (default 1); higher means more urgent.
     */
    EventNotice(const std::string& type, const std::string& sector, const std::string& message, int severity = 1);

    /**
     * @brief Returns the notice's kind, e.g. "RED_FLAG".
     * @return const reference to the type string.
     */
    const std::string& getType() const;

    /**
     * @brief Returns the sector this notice concerns.
     * @return const reference to the sector string ("" means all sectors).
     */
    const std::string& getSector() const;

    /**
     * @brief Returns the human-readable message for this notice.
     * @return const reference to the message string.
     */
    const std::string& getMessage() const;

    /**
     * @brief Returns this notice's severity level.
     * @return int severity (higher is more urgent).
     */
    int getSeverity() const;

    /**
     * @brief Builds a one-line human-readable summary of this notice.
     * @return Formatted string combining type, sector and message.
     */
    std::string toString() const;
};
#endif
