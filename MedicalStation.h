#ifndef MEDICALSTATION_H
#define MEDICALSTATION_H
#include <EventUnit.h>
class MedicalStation : public EventUnit {
    private:
    public:
    MedicalStation(const std::string& name):EventUnit(name){}
    virtual ~MedicalStation();
    virtual void open() override;
    virtual void close() override;
    virtual void reportStatus() const override;
    virtual void getCapacity() const override;
};
#endif