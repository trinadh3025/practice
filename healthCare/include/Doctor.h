#ifndef DOCTOR_H
#define DOCTOR_H

#include "DoctorPersonalInfo.h"
#include <string>
#include <vector>
#include <memory>

class Doctor{
public:
	int id;
	std::string speciality;
	std::vector<std::string> availability;
	std::shared_ptr<DoctorPersonalInfo> personalInfo;
	
	Doctor();
	Doctor(int id, const std::string &speciality,
	       const std::vector<std::string> &availability,
	       const std::shared_ptr<DoctorPersonalInfo> personalInfo);
	void displayDetails();
	bool isAvailable(const std::string &slot);
	void allocateSlot(const std::string &slot);
	void saveToJSON(const std::string &fileName);
	void loadFromJSON(const std::string &fileName);
};
#endif
