#pragma once
#include <EventUnit.h>
class TimingPoint : public EventUnit {
    private:
    public:
    virtual ~TimingPoint();
    TimingPoint(const std::string& name):EventUnit(name){}
    virtual void open() override;
    virtual void close() override;
    virtual void reportStatus() const override;
    virtual void getCapacity() const override;
};
