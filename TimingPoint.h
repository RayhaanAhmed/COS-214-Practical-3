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
    TimingPoint(const std::string& name);
    virtual ~TimingPoint();

    virtual void open() override;
    virtual void close() override;
    virtual void reportStatus() const override;
    virtual int getCapacity() const override;
    virtual void update(const EventNotice& notice) override;

    /**
     * @brief Specs 4.4 original feature = lap record tracking.
     * Records a completed lap only while timing is active (ignored during a red-flag freeze) 
     * and announces a new track record when beaten.
     */
    void recordLap(double lapSeconds);
};
#endif
