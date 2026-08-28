#include <leaves/MarshalPost.h>
void MarshalPost::open() {
    std::cout << m_name << " opened.\n";
}
void MarshalPost::close() {
    std::cout << m_name << " closed.\n";
}
void MarshalPost::reportStatus() const {
    std::cout << m_name << ":\n";
}
void MarshalPost::getCapacity() const {

}
MarshalPost::~MarshalPost(){}