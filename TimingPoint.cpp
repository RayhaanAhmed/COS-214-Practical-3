#include <TimingPoint.h>
void TimingPoint::open() {
    std::cout << m_name << " opened.\n";
}
void TimingPoint::close() {
    std::cout << m_name << " closed.\n";
}
void TimingPoint::reportStatus() const {
    std::cout << m_name << ":\n";
}
void TimingPoint::getCapacity() const {

}
TimingPoint::~TimingPoint(){}
