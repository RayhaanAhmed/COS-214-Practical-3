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
/**
     * @brief Constructs a safety car, initially in the pit.
     * @param name Display name for this safety car.
     */
    SafetyCar(const std::string& name);

    /// @brief Virtual destructor (Leaf, no owned children).
    virtual ~SafetyCar();

    /// @brief Marks the safety car available (in pit).
    virtual void open() override;

    /// @brief Marks the safety car unavailable.
    virtual void close() override;

    /// @brief Prints this safety car's current status.
    virtual void reportStatus() const override;

    /**
     * @brief This leaf doesn't hold people/vehicles.
     * @return int always 0.
     */
    virtual int getCapacity() const override;

    /**
     * @brief Deploys onto the circuit for RED_FLAG/MEDICAL_INCIDENT,
     * returns to the pit lane on RESUME.
     * @param notice The notice received from this car's Subject.
     */
    virtual void update(const EventNotice& notice) override;
};
#endif
