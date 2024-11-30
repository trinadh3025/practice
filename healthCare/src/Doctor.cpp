#include "Doctor.h"
#include <json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

Doctor::Doctor(){
	id = -1;
	speciality = "N/A";
	availability = {"N/A"};
	personalInfo = std::make_shared<DoctorPersonalInfo>();

}
Doctor::Doctor(int id, const std::string &speciality,
	       const std::vector<std::string> &availability,
	       std::shared_ptr<DoctorPersonalInfo> personalInfo)
		: id(id), speciality(speciality), availability(availability),
		  personalInfo(personalInfo) {}

void Doctor::displayDetails(){
	std::cout << "Doctor id: " << id << "\n"
		  << "Speciality: " << speciality << std::endl;
	personalInfo->displayPersonalInfo();
}

bool Doctor::isAvailable(const std::string &slot){
	return std::find(availability.begin(), availability.end(), slot) != availability.end();
}

void Doctor::allocateSlot(const std::string &slot){
	auto it = std::find(availability.begin(), availability.end(), slot);
	if( it != availability.end()){
		availability.erase(it);
		std::cout << "Slot " << slot << " allocated successfully" << std::endl;
	}
}

void Doctor::saveToJSON(const std::string &fileName){
	json j = {{"id", id},
		  {"speciality", speciality},
		  {"availability",availability}};
	json personal = {{"name", personalInfo->name},
		          {"contact", personalInfo->contact},
			  {"qualification",personalInfo->qualification}};
	j["personalInfo"] = personal;

	std::ofstream file(fileName, std::ios::app);
	file << j.dump() << std::endl;
	file.close();
	
}
