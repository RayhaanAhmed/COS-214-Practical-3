#include "EventControl.h"
#include "EventNotice.h"
#include <iostream>

EventControl::EventControl(EventGroup* root) : m_root(root) {}

void EventControl::issueNotice(const EventNotice& notice) {
    std::cout << "\n=== EventControl issues " << notice.toString() << " ===\n";
    notify(notice);
}
