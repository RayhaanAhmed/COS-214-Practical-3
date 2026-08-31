#ifndef PITGARAGE_H
#define PITGARAGE_H
#include "EventComponent.h"
#include "Observer.h"
#include <queue>
#include <string>

/**
 * @brief Pit garage bay. Leaf, Observer of its zone.
 * Holds queued cars; RED_FLAG closes the lane, RESUME releases the
 * queue in FIFO order.
 */
class PitGarage : public EventComponent, public Observer {
    bool m_laneOpen;
    std::queue<std::string> m_releaseQueue;
    int m_capacity;
    bool m_speedLimited; ///< SPEC 4.4 feature 3 — see update()

public:
    /**
     * @brief Constructs a pit garage.
     * @param name Display name for this garage.
     * @param capacity Maximum number of cars this garage can queue.
     */
    PitGarage(const std::string& name, int capacity = 4);

    /// @brief Virtual destructor (Leaf, no owned children).
    virtual ~PitGarage();

    /// @brief Marks the garage's lane open.
    virtual void open();
    
     /// @brief Marks the garage's lane closed.
    virtual void close();

    /// @brief Prints this garage's current status.
    virtual void reportStatus() const;

    /**
     * @brief Returns this garage's queue capacity.
     * @return int number of cars this garage can hold.
     */
    virtual int getCapacity() const;

    /**
     * @brief update() also implements SPEC 4.4 — ORIGINAL FEATURE 3:
     * weather-triggered pit-lane speed limit. Not required by the
     * spec. A WEATHER_ALERT imposes a speed limit that RESUME lifts;
     * this is independent of the lane-open/closed state a RED_FLAG
     * controls, giving the pit lane two orthogonal safety states
     * instead of overloading one boolean.
     * @param notice The notice received from this garage's Subject.
     */
    virtual void update(const EventNotice& notice);

    /**
     * @brief Adds a car to the release queue if capacity allows.
     * @param car Identifier for the car being queued.
     */
    void enqueueCar(const std::string& car);
};
#endif
