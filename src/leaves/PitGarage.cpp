#include <leaves/PitGarage.h>
void PitGarage::open() {
    std::cout << m_name << " opened.\n";
}
void PitGarage::close() {
    std::cout << m_name << " closed.\n";
}
void PitGarage::reportStatus() const {
    std::cout << m_name << ":\n";
}
void PitGarage::getCapacity() const {

}
PitGarage::~PitGarage(){}