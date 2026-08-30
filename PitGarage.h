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
    PitGarage(const std::string& name, int capacity = 4);
    virtual ~PitGarage();

    virtual void open() override;
    virtual void close() override;
    virtual void reportStatus() const override;
    virtual int getCapacity() const override;

    /**
     * @brief update() also implements SPEC 4.4 — ORIGINAL FEATURE 3:
     * weather-triggered pit-lane speed limit. Not required by the
     * spec. A WEATHER_ALERT imposes a speed limit that RESUME lifts;
     * this is independent of the lane-open/closed state a RED_FLAG
     * controls, giving the pit lane two orthogonal safety states
     * instead of overloading one boolean.
     */
    virtual void update(const EventNotice& notice) override;

    void enqueueCar(const std::string& car);
};
#endif
