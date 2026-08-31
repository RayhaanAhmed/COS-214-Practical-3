#ifndef EVENT_GROUP_H
#define EVENT_GROUP_H
#include "EventComponent.h"
#include "Subject.h"
#include "Observer.h"
#include <vector>
#include <string>

/**
 * @brief Composite grouping of EventComponents (a Zone/Sector/etc.).
 * GoF roles:
 * Composite (of EventComponent): owns children and recursively
 * delegates open/close/reportStatus/getCapacity to them.
 * Subject: notifies its own children when it receives a notice
 * worth forwarding.
 * Observer: registers with its parent EventGroup (or EventControl)
 * to receive notices from above.
 * These are two distinct collaborations over disjoint object sets
 * (children below vs parent above) and not a misuse of either pattern.
 * Ownership: children are owned (deleted in the destructor). Observer
 * registration is separate and non-owning.
 */
class EventGroup : public EventComponent, public Subject, public Observer {
    std::vector<EventComponent*> m_children; //OWNED

public:
/**
     * @brief Constructs an empty group with the given display name.
     * @param name Human-readable name for this group.
     */
    EventGroup(const std::string& name) : EventComponent(name) {};

    /// @brief Deletes every owned child exactly once, then clears the list.
    virtual ~EventGroup();

    /**
     * @brief Adds a child and, if it is also an Observer, registers it
     * to receive this group's future notifications.
     * Design decision: add() auto-registers an observable child. This
     * is what makes cascading notification work without a separate
     * manual wiring step, and is documented as a deliberate coupling.
     * @param c Child component to add. Ownership transfers to this group.
     */
    void add(EventComponent* c);

    /**
     * @brief Removes a child without deleting it and deregisters it as
     * an observer of this group. The caller becomes responsible for
     * the pointer (typically by add()-ing it to a different EventGroup
     * immediately and is used for runtime reorganisation).
     * @param c Child component to remove. Not deleted by this call.
     */
    void remove(EventComponent* c);

    /// @brief Opens this group by recursively opening every child.
    virtual void open()  ;

    /// @brief Closes this group by recursively closing every child.
    virtual void close()  ;

    /// @brief Prints this group's status, then recursively each child's.
    virtual void reportStatus() const  ;

    /**
     * @brief Recursively sums the capacity of every child.
     * @return int total capacity of the subtree rooted at this group.
     */
    virtual int getCapacity() const  ;

    /**
     * @brief Receives a notice from this group's parent Subject and
     * cascades it to this group's own children via notify(). This is
     * the Observer-then-Subject hop that makes multi-level cascading
     * notification work.
     * @param notice The notice received from above, forwarded unchanged.
     */
    virtual void update(const EventNotice& notice)  ;

    /**
     * @brief Returns this group's owned children.
     * @return const reference to the vector of child component pointers.
     */
    const std::vector<EventComponent*>& getChildren() const { return m_children; }

    /**
     * @brief SPEC 4.3: condition-based decision
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
