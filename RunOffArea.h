#ifndef RUNOFFAREA_H
#define RUNOFFAREA_H
#include <EventUnit.h>
class RunOffArea : public EventUnit {
    private:
    public:
    virtual ~RunOffArea();
    RunOffArea(const std::string& name):EventUnit(name){}
    virtual void open() override;
    virtual void close() override;
    virtual void reportStatus() const override;
    virtual void getCapacity() const override;
};
#endif