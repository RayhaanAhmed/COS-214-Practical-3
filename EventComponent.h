#ifndef EVENT_COMPONENT_H
#define EVENT_COMPONENT_H
#include <iostream>
#include <string>

/**
 * @brief Common Component interface for the Composite pattern.
 * Both individual event units (concrete Leaf classes) and groups of units
 * (EventGroup composites) implement this interface uniformly, so a
 * client can open/close/report on either a single unit or an entire
 * subtree without knowing which.
 * GoF role: Component.
 */
class EventComponent {
protected:
    std::string m_name;

public:
    EventComponent(const std::string& name) : m_name(name) {};

    /// @brief Every polymorphic base must have a virtual destructor.
    virtual ~EventComponent() = default;

    virtual void open() = 0;
    virtual void close() = 0;
    virtual void reportStatus() const = 0;

    /**
     * @brief Returns this component's capacity.
     * @return int capacity (0 for units that don't hold people/vehicles).
     */
    virtual int getCapacity() const = 0;

    const std::string& getName() const { return m_name; }
};
#endif
