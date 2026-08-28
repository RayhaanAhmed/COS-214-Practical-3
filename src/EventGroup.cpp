#include <EventGroup.h>
void EventGroup::add(EventComponent* c)
{
    m_children.push_back(c);
}
void EventGroup::remove(EventComponent* c)
{
    for (auto it = m_children.begin(); it != m_children.end(); ++it) {
        if (*it == c)
        {
            m_children.erase(it);
            return;
        }
    }
}

EventGroup::~EventGroup() {
    for(EventComponent* c : m_children) {
        delete c;
    }
}

void EventGroup::open() {
    std::cout << m_name << " opened.\n";
}
void EventGroup::close() {
    std::cout << m_name << " closed.\n";
}
void EventGroup::reportStatus() const {
    std::cout << m_name << ":\n";
}
void EventGroup::getCapacity() const {

}