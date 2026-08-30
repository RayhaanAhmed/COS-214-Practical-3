#ifndef SAFETYCAR_H
#define SAFETYCAR_H
#include "EventComponent.h"
#include "Observer.h"
#include <string>

/**
 * @brief Specs 4.4 Orginal feature 
 * Safety car. A 7th concrete leaf type, Observer of its zone. 
 * Automatically deploys onto the circuit when a RED_FLAG/MEDICAL_INCIDENT issued
 * returns to the pit lane on RESUME.
 * This is a standalone leaf (it doesn't touch any other class) so it adds a new interaction.
 */
class SafetyCar : public EventComponent, public Observer {
    std::string m_status; // "in pit" or "deployed"

public:
    SafetyCar(const std::string& name);
    virtual ~SafetyCar();
    virtual void open() override;
    virtual void close() override;
    virtual void reportStatus() const override;
    virtual int getCapacity() const override;
    virtual void update(const EventNotice& notice) override;
};
#endif
