#ifndef GRANDSTAND_H
#define GRANDSTAND_H
#include "EventComponent.h"
#include "Observer.h"
#include <string>

/**
 * @brief Spectator grandstand. Leaf, Observer of its zone.
 * Deliberately resilient: stays open through YELLOW_FLAG/WEATHER_ALERT,
 * only closes on EVACUATE. Tracks occupancy against capacity.
 */
class Grandstand : public EventComponent, public Observer {
    bool m_open;
    int m_capacity;
    int m_occupancy;

    /// @brief Occupancy ratio (0.0-1.0) at/above which entry is held.
    /// SPEC 4.3: named, reusable threshold used in an explicit condition
    /// with guards [occupancy/capacity >= THRESHOLD] / [else] in SD3.
    static constexpr double CAPACITY_THRESHOLD = 0.9;

public:
/**
     * @brief Constructs a grandstand.
     * @param name Display name for this grandstand.
     * @param capacity Maximum spectator capacity.
     */
    Grandstand(const std::string& name, int capacity = 300);

    /// @brief Virtual destructor (Leaf, no owned children).
    virtual ~Grandstand();

    /// @brief Marks the grandstand open.
    virtual void open();

    /// @brief Marks the grandstand closed.
    virtual void close();

    /// @brief Prints this grandstand's current status.
    virtual void reportStatus() const;

    /**
     * @brief Returns this grandstand's spectator capacity.
     * @return int maximum capacity.
     */
    virtual int getCapacity() const;

    /**
     * @brief Reacts to EVACUATE (closes), CAPACITY_ALERT (checks occupancy
     * against CAPACITY_THRESHOLD), RESUME (reopens), stays open through
     * YELLOW_FLAG/WEATHER_ALERT.
     * @param notice The notice received from this grandstand's Subject.
     */
    virtual void update(const EventNotice& notice);

    /**
     * @brief Sets the current spectator occupancy.
     * @param count Number of spectators currently present.
     */
    void setOccupancy(int count);
};
#endif
