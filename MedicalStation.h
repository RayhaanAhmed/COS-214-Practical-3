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
    MedicalStation(const std::string& name);
    virtual ~MedicalStation();

    virtual void open() override;
    virtual void close() override;
    virtual void reportStatus() const override;
    virtual int getCapacity() const override;
    virtual void update(const EventNotice& notice) override;
};
#endif