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

    // Number of RED_FLAG incidents this post has handled before it requests reinforcement.
    static const int REINFORCEMENT_THRESHOLD = 3;

public:
/**
     * @brief Constructs a marshal post, initially showing green.
     * @param name Display name for this post.
     */
    MarshalPost(const std::string& name);

    /// @brief Virtual destructor (Leaf, no owned children).
    virtual ~MarshalPost();

    /// @brief Marks the post operational.
    virtual void open();

    /// @brief Marks the post non-operational.
    virtual void close();

    /// @brief Prints this post's current status.
    virtual void reportStatus() const;

    /**
     * @brief This leaf doesn't hold people/vehicles.
     * @return int always 0.
     */
    virtual int getCapacity() const;

    /**
     * @brief update() also implements SPEC 4.4 = ORIGINAL FEATURE 2:
     * incident-count escalation. Each RED_FLAG this post handles increments a counter,
     * after REINFORCEMENT_THRESHOLD incidents it prints a reinforcement
     * request. Self-contained (own counter, own threshold) so it does
     * not pull MarshalPost toward being a god object. Also
     * auto-escalates to RED on severe (severity >= 4) WEATHER_ALERT.
     * @param notice The notice received from this post's Subject.
     */
    virtual void update(const EventNotice& notice);
};
#endif
