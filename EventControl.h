#ifndef EVENTCONTROL_H
#define EVENTCONTROL_H
#include "Subject.h"
#include "EventGroup.h"
#include <string>

/**
 * @brief Root-level notice originator. Concrete Subject.
 *
 * EventControl is deliberately NOT part of the Composite tree (not an
 * EventComponent) — it is the client/coordinator that issues top-level
 * notices. It holds a pointer to the root EventGroup for traversal
 * convenience only, not ownership.
 */
class EventControl : public Subject {
    EventGroup* m_root; ///< non-owning: root lifetime is managed by main()

public:
    explicit EventControl(EventGroup* root);
    void issueNotice(const EventNotice& notice);
    EventGroup* getRoot() const { return m_root; }
};
#endif
