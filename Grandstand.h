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
    Grandstand(const std::string& name, int capacity = 300);
    virtual ~Grandstand();

    virtual void open() override;
    virtual void close() override;
    virtual void reportStatus() const override;
    virtual int getCapacity() const override;
    virtual void update(const EventNotice& notice) override;

    void setOccupancy(int count);
};
#endif
