#ifndef OBSERVER_H
#define OBSERVER_H

class EventNotice;

/**
 * @brief Abstraction for anything that can receive a pushed EventNotice.
 * GoF role: Observer. This project uses push semantics. The full
 * notice payload travels with update(), so implementers don't need to
 * query the subject afterward.
 */
class Observer {
public:
    virtual ~Observer(){};

    /**
     * @brief Called by a Subject when a relevant notice is issued.
     * @param notice The full notice payload (push style).
     */
    virtual void update(const EventNotice& notice) = 0;
};
#endif
