#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "Patient.h"
#include "Doctor.h"
#include <string>
#include <memory>

class Appointment {
public:
	std::shared_ptr<Patient> patient;
	std::shared_ptr<Doctor> doctor;
	std::string timeSlot;
	std::string symptoms;

	Appointment(std::shared_ptr<Patient> patient, std::shared_ptr<Doctor> doctor,
			const std::string &timeSlot, const std::string &symptoms);
	void displayDetails() const;
	void saveToJSON(const std::string &fileName);
	static std::vector<std::shared_ptr<Appointment>> loadFromJSON(const std::string &fileName);
};

#endif
