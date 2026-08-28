#include <leaves/RunOffArea.h>
void RunOffArea::open() {
    std::cout << m_name << " opened.\n";
}
void RunOffArea::close() {
    std::cout << m_name << " closed.\n";
}
void RunOffArea::reportStatus() const {
    std::cout << m_name << ":\n";
}
void RunOffArea::getCapacity() const {

}
RunOffArea::~RunOffArea(){}