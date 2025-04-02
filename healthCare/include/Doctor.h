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

	/*
	void setId(int id_){
		this->id = id;
	}

	int getId(){
		return this->id;
	}
	
	void setSpeciality(std::string speciality_){
		this->speciality = speciality_;
	}

	std::string getSpeciality(){
		return this->speciality;
	}
	

	std::vector<std::string>> getAvailability(){
		return this->availability;
	}

	void setAvailability(std::string time){
		availability.push_back(time);
	}
	void setAvailability(std::vector<std::string>> availability_){
		availability = availability_;
	}
	*/
};
#endif
