#ifndef PITGARAGE_H
#define PITGARAGE_H
#include <EventUnit.h>
class PitGarage : public EventUnit {
    private:
    public:
    virtual ~PitGarage();
    PitGarage(const std::string& name):EventUnit(name){}
    virtual void open() override;
    virtual void close() override;
    virtual void reportStatus() const override;
    virtual void getCapacity() const override;
};
#endif