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
    /**
     * @brief Constructs a run-off area, initially clear.
     * @param name Display name for this area.
     */
    RunOffArea(const std::string& name);

     /// @brief Virtual destructor (Leaf, no owned children).
    virtual ~RunOffArea();

    /// @brief Marks the area open (no-op beyond status if already open).
    virtual void open();

    /// @brief Marks the area closed.
    virtual void close();

    /// @brief Prints this area's current status.
    virtual void reportStatus() const;

    /**
     * @brief This leaf doesn't hold people/vehicles.
     * @return int always 0.
     */
    virtual int getCapacity() const;

    /**
     * @brief Reacts to RED_FLAG (closes) and RESUME (reopens).
     * @param notice The notice received from this area's Subject.
     */
    virtual void update(const EventNotice& notice);
};
#endif
