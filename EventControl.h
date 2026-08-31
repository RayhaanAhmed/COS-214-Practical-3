#ifndef EVENTCONTROL_H
#define EVENTCONTROL_H
#include "Subject.h"
#include "EventGroup.h"
#include <string>

/**
 * @brief Root-level notice originator. Concrete Subject.
 * EventControl is deliberately NOT part of the Composite tree (not an
 * EventComponent) — it is the client/coordinator that issues top-level
 * notices. It holds a pointer to the root EventGroup for traversal
 * convenience only, not ownership.
 */
class EventControl : public Subject {
    EventGroup* m_root; //non-owning: root lifetime is managed by main()

public:
/**
     * @brief Constructs the control, pointing it at the tree's root.
     * @param root Root of the Composite tree this control coordinates.
     * Not owned as its lifetime is managed by main().
     */
    EventControl(EventGroup* root);

    /**
     * @brief Issues a notice to every top-level EventGroup registered
     * with this control, which then cascades it down the tree.
     * @param notice The notice to push out.
     */
    void issueNotice(const EventNotice& notice);

    /**
     * @brief Returns the root of the Composite tree this control coordinates.
     * @return EventGroup* pointer to the root (non-owning).
     */
    EventGroup* getRoot() const { return m_root; }
};
#endif
