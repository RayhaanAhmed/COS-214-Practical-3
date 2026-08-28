#ifndef EVENT_UNIT_H
#define EVENT_UNIT_H
#include <EventComponent.h>
#include <string>

class EventUnit : public EventComponent {
public:
    EventUnit(const std::string& name):EventComponent(name){};
    virtual ~EventUnit() = default;
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void reportStatus() const = 0;
    virtual void getCapacity() const = 0;
};
#endif