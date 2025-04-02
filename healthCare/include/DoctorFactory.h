#ifndef DOCTOR_FACTORY_H
#define DOCTOR_FACTORY_H

#include "EntityFactory.h"
#include "Doctor.h"

class DoctorFactory: public EntityFactory{
public:
	std::shared_ptr<void> createEntity() const override{
		return std::make_shared<Doctor>();
	}
};
#endif
