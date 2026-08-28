#include <Grandstand.h>
void Grandstand::open() {
    std::cout << m_name << " opened.\n";
}
void Grandstand::close() {
    std::cout << m_name << " closed.\n";
}
void Grandstand::reportStatus() const {
    std::cout << m_name << ":\n";
}
void Grandstand::getCapacity() const {

}
Grandstand::~Grandstand(){}