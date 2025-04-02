#ifndef PATIENT_FACTORY_H
#define PATIENT_FACTORY_H

#include "EntityFactory.h"
#include "Patient.h"

class PatientFactory: public EntityFactory{
public:
	std::shared_ptr<void> createEntity() const override{
		return std::make_shared<Patient>();
	}
};
#endif
