#pragma once
#include <EventUnit.h>
class MarshalPost : public EventUnit {
    private:
    public:
    virtual ~MarshalPost();
    MarshalPost(const std::string& name):EventUnit(name){}
    virtual void open() override;
    virtual void close() override;
    virtual void reportStatus() const override;
    virtual void getCapacity() const override;
};
