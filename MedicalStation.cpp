#include <leaves/MedicalStation.h>
void MedicalStation::open() {
    std::cout << m_name << " opened.\n";
}
void MedicalStation::close() {
    std::cout << m_name << " closed.\n";
}
void MedicalStation::reportStatus() const {
    std::cout << m_name << ":\n";
}
void MedicalStation::getCapacity() const {

}
MedicalStation::~MedicalStation(){}