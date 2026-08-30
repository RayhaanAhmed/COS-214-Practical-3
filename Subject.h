#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <algorithm>
#include "Observer.h"

class EventNotice;

/**
 * @brief Abstraction for anything that can be observed.
 * GoF role: Subject. Stores a non-owning registration list of Observer
 * pointers. attach()/detach() manage that list, notify() pushes an
 * EventNotice to every currently registered observer.
 * Ownership policy: the Subject does NOT own its observers. Each observer must 
 * detach itself before destruction so no Subject is left holding a dangling pointer.
 */
class Subject {
private:
    std::vector<Observer*> m_observers; // non-owning

public:
    virtual ~Subject() = default;

    /**
     * @brief Registers an observer for future notifications.
     * Duplicate registration policy: if the pointer is already
     * registered, this call is a no-op.
     * @param observer Observer to register. Must not be nullptr.
     */
    virtual void attach(Observer* observer) {
        if (!observer) return;
        if (std::find(m_observers.begin(), m_observers.end(), observer) == m_observers.end()) {
            m_observers.push_back(observer);
        }
    }

    /**
     * @brief Deregisters an observer.
     * If the observer isn't currently registered, this is a no-op
     * covers both double-detach and detaching an unregistered observer.
     */
    virtual void detach(Observer* observer) {
        m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
    }

    /**
     * @brief Pushes a notice to every currently registered observer.
     * Iterates a snapshot copy so an observer that attaches/detaches
     * during its own update() cannot invalidate iteration in progress.
     */
    virtual void notify(const EventNotice& notice) {
        std::vector<Observer*> snapshot = m_observers;
        for (Observer* obs : snapshot) {
            if (obs) obs->update(notice);
        }
    }

    size_t observerCount() const { return m_observers.size(); }
};
#endif
