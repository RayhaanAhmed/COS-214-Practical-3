#ifndef EVENT_COMPONENT_H
#define EVENT_COMPONENT_H
#include <iostream>
#include <string>
class EventComponent {
protected:
    std::string m_name;
    
public:
    EventComponent(const std::string& name):m_name(name){};
    virtual ~EventComponent() = default;
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void reportStatus() const = 0;
    virtual void getCapacity() const = 0;
};
#endif