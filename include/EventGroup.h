#pragma once
#include <EventComponent.h>
#include <vector>
#include <string>
class EventGroup : public EventComponent {
    std::vector<EventComponent*> m_children;

    public:
    EventGroup(const std::string& name):EventComponent(name){};
    void add(EventComponent* c);
    void remove(EventComponent* c);
    virtual ~EventGroup();
    virtual void open() override;
    virtual void close() override;
    virtual void reportStatus() const override;
    virtual void getCapacity() const override;
};