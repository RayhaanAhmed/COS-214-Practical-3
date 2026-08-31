#ifndef MEDICALSTATION_H
#define MEDICALSTATION_H
#include "EventComponent.h"
#include "Observer.h"
#include <string>

/**
 * @brief Medical response point. Leaf, Observer of its zone.
 * Never fully "closes" changes an internal readiness state
 * (standby -> deployed) instead, since it must stay reachable through
 * every alert type.
 */
class MedicalStation : public EventComponent, public Observer {
    std::string m_readiness; //"standby" or "deployed"

public:
/**
     * @brief Constructs a medical station, initially on standby.
     * @param name Display name for this station.
     */
    MedicalStation(const std::string& name);

    /// @brief Virtual destructor (Leaf, no owned children).
    virtual ~MedicalStation();

    /// @brief Marks the station open.
    virtual void open();

    /// @brief Marks the station closed.
    virtual void close();

    /// @brief Prints this station's current status.
    virtual void reportStatus() const;

    /**
     * @brief This leaf doesn't hold people/vehicles.
     * @return int always 0.
     */
    virtual int getCapacity() const;

    /**
     * @brief Escalates to "deployed" for RED_FLAG/MEDICAL_INCIDENT/EVACUATE,
     * returns to "standby" on RESUME, otherwise stays operational.
     * @param notice The notice received from this station's Subject.
     */
    virtual void update(const EventNotice& notice);
};
#endif