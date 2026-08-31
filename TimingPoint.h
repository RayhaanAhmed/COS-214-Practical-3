#ifndef TIMINGPOINT_H
#define TIMINGPOINT_H
#include "EventComponent.h"
#include "Observer.h"
#include <string>

/**
 * @brief Lap timing loop. Leaf, Observer of its sector.
 * Freezes timing on RED_FLAG, resumes on RESUME.
 */
class TimingPoint : public EventComponent, public Observer {
    bool m_timingActive;
    int m_lapsRecorded;
    double m_bestLapSeconds; //extra

public:
    /**
     * @brief Constructs a timing point, initially active.
     * @param name Display name for this timing point.
     */
    TimingPoint(const std::string& name);

    /// @brief Virtual destructor (Leaf, no owned children).
    virtual ~TimingPoint();

    /// @brief Marks the timing point open.
    virtual void open() override;

    /// @brief Marks the timing point closed.
    virtual void close() override;

    /// @brief Prints this timing point's current status.
    virtual void reportStatus() const override;

    /**
     * @brief This leaf doesn't hold people/vehicles.
     * @return int always 0.
     */
    virtual int getCapacity() const override;

    /**
     * @brief Reacts to RED_FLAG (freezes timing) and RESUME (resumes).
     * @param notice The notice received from this point's Subject.
     */
    virtual void update(const EventNotice& notice) override;

    /**
     * @brief Specs 4.4 original feature = lap record tracking.
     * Records a completed lap only while timing is active (ignored during a red-flag freeze) 
     * and announces a new track record when beaten. Fits TimingPoint's single
     * responsibility (it already owns lap state) so it doesn't turn
     * TimingPoint into a god object — it's the same data the class
     * already tracks, just used to derive one more fact from it.
     * @param lapSeconds Time in seconds for the completed lap.
     */
    void recordLap(double lapSeconds);
};
#endif
