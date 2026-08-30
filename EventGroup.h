#ifndef EVENT_GROUP_H
#define EVENT_GROUP_H
#include "EventComponent.h"
#include "Subject.h"
#include "Observer.h"
#include <vector>
#include <string>

/**
 * @brief Composite grouping of EventComponents (a Zone/Sector/etc.).
 *
 * GoF roles:
 *  - Composite (of EventComponent): owns children and recursively
 *    delegates open/close/reportStatus/getCapacity to them.
 *  - Subject: notifies its own children when it receives a notice
 *    worth forwarding.
 *  - Observer: registers with its parent EventGroup (or EventControl)
 *    to receive notices from above.
 * These are two distinct collaborations over disjoint object sets
 * (children below vs parent above) — not a misuse of either pattern.
 *
 * Ownership: children are owned (deleted in the destructor). Observer
 * registration is separate and non-owning.
 */
class EventGroup : public EventComponent, public Subject, public Observer {
    std::vector<EventComponent*> m_children; ///< OWNED

public:
    EventGroup(const std::string& name) : EventComponent(name) {};

    /// @brief Deletes every owned child exactly once, then clears the list.
    virtual ~EventGroup();

    /**
     * @brief Adds a child and, if it is also an Observer, registers it
     * to receive this group's future notifications.
     *
     * Design decision: add() auto-registers an observable child. This
     * is what makes cascading notification work without a separate
     * manual wiring step, and is documented as a deliberate coupling.
     */
    void add(EventComponent* c);

    /**
     * @brief Removes a child without deleting it and deregisters it as
     * an observer of this group. The caller becomes responsible for
     * the pointer (typically by add()-ing it to a different EventGroup
     * immediately — used for runtime reorganisation).
     */
    void remove(EventComponent* c);

    virtual void open() override;
    virtual void close() override;
    virtual void reportStatus() const override;
    virtual int getCapacity() const override;

    /**
     * @brief Receives a notice from this group's parent Subject and
     * cascades it to this group's own children via notify(). This is
     * the Observer-then-Subject hop that makes multi-level cascading
     * notification work.
     */
    virtual void update(const EventNotice& notice) override;

    const std::vector<EventComponent*>& getChildren() const { return m_children; }

    /**
     * @brief === SPEC 4.3: condition-based decision ===
     * Compares a given occupancy reading against this group's recursive
     * getCapacity() and decides whether to self-issue a CAPACITY_ALERT
     * to this group's own observers. Two-branch decision
     * ([occupancy >= capacity] / [else]) — maps directly onto a UML
     * `alt` combined fragment with those two guards in SD3.
     * @param currentOccupancy A simulated occupancy reading for this group.
     */
    void checkCapacityThreshold(int currentOccupancy);
};
#endif
