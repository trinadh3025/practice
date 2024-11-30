#ifndef MEDICALHISTORY_H
#define MEDICALHISTORY_H

#include "Doctor.h"
#include <string>
#include <memory>

class MedicalHistory{
public:
	std::string previousHospital;
	std::shared_ptr<Doctor> doctor;
	std::string pastTreatment;

	MedicalHistory();
	MedicalHistory(const std::string &previousHospital, std::shared_ptr<Doctor> doctor,
			const std::string &pastTreatment);
	void displayRecord() const;
};
#endif
