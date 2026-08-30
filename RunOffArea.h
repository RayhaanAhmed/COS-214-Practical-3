#ifndef RUNOFFAREA_H
#define RUNOFFAREA_H
#include "EventComponent.h"
#include "Observer.h"
#include <string>

/**
 * @brief Gravel/run-off zone. Leaf, Observer of its sector.
 * Closes the run-off line during RED_FLAG (marshals working on track), reopens on RESUME.
 */
class RunOffArea : public EventComponent, public Observer {
    bool m_clear;

public:
    RunOffArea(const std::string& name);
    virtual ~RunOffArea();
    virtual void open() override;
    virtual void close() override;
    virtual void reportStatus() const override;
    virtual int getCapacity() const override;
    virtual void update(const EventNotice& notice) override;
};
#endif
