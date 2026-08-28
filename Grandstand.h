#ifndef GRANDSTAND_H
#define GRANDSTAND_H
#include <EventUnit.h>
class Grandstand : public EventUnit {
    private:
    public:
    virtual ~Grandstand();
    Grandstand(const std::string& name):EventUnit(name){}
    virtual void open() override;
    virtual void close() override;
    virtual void reportStatus() const override;
    virtual void getCapacity() const override;
};
#endif