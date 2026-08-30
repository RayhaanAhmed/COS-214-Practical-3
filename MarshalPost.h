#ifndef MARSHALPOST_H
#define MARSHALPOST_H
#include "EventComponent.h"
#include "Observer.h"
#include <string>

/**
 * @brief Trackside flag point. Leaf, Observer of its zone/sector.
 * Displays a flag state and reacts differently to RED vs YELLOW.
 */
class MarshalPost : public EventComponent, public Observer {
    std::string m_currentFlag; //"green", "yellow", "red"
    bool m_operational;
    int m_incidentCount; // SPECS 4.4 feature 2 (see update())

    // Number of RED_FLAG incidents this post has handled before it
    // requests reinforcement.
    static const int REINFORCEMENT_THRESHOLD = 3;

public:
    MarshalPost(const std::string& name);
    virtual ~MarshalPost();

    virtual void open() override;
    virtual void close() override;
    virtual void reportStatus() const override;
    virtual int getCapacity() const override;

    /**
     * @brief update() also implements 4.4 (original feature)
     * incident-count escalation. Each RED_FLAG this post handles increments 
     * a counter; after REINFORCEMENT_THRESHOLD incidents it prints a 
     * reinforcement request. Self-contained (own counter, own threshold) so it does
     * not pull MarshalPost toward being a god object.
     */
    virtual void update(const EventNotice& notice) override;
};
#endif
