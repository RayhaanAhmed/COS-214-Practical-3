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
/**
     * @brief Constructs a component with the given display name.
     * @param name Human-readable name for this component.
     */
    EventComponent(const std::string& name) : m_name(name) {};

    /// @brief Every polymorphic base must have a virtual destructor.
    virtual ~EventComponent(){};

    /// @brief Opens this component (and, for a Composite, its children)
    virtual void open() = 0;

    /// @brief Closes this component (and, for a Composite, its children)
    virtual void close() = 0;

    /// @brief Prints this component's current status.
    virtual void reportStatus() const = 0;

    /**
     * @brief Returns this component's capacity.
     * @return int capacity (0 for units that don't hold people/vehicles).
     */
    virtual int getCapacity() const = 0;

    /**
     * @brief Returns this component's display name.
     * @return const reference to the stored name.
     */
    const std::string& getName() const { return m_name; }
};
#endif
