#include "DoctorPersonalInfo.h"
#include <json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

DoctorPersonalInfo::DoctorPersonalInfo(){
	name = "N/A";
	contact = "N/A";
	qualification = "N/A";
}
DoctorPersonalInfo::DoctorPersonalInfo(const std::string &name,
				       const std::string &contact,
				       const std::string &qualification):
					name(name), contact(contact),
					qualification(qualification){}

void DoctorPersonalInfo::displayPersonalInfo(){
	std::cout << "Name: " << name << "\n" 
		 << "Contact: " << contact << "\n"
		 << "Qualification: " << qualification << std::endl;

}

void DoctorPersonalInfo::saveToJSON(const std::string &fileName){
	json j = {{"name", name},
		  {"contact",contact},
		  {"qualification",qualification}
		};
	std::ofstream file(fileName, std::ios::app);
	file << j.dump() << std::endl;
	file.close();
}

std::vector<std::shared_ptr<DoctorPersonalInfo>> DoctorPersonalInfo::loadFromJSON(
		const std::string &fileName){
	std::vector<std::shared_ptr<DoctorPersonalInfo>> infoList;
	std::ifstream file(fileName);
	if (file.is_open()){
		std::string line;
		while (std::getline(file, line)){
			json j = json::parse(line);
			infoList.push_back(std::make_shared<DoctorPersonalInfo>(j["name"],
										j["contact"],
										j["qualification"]));
		}
		file.close();
	}
	return infoList;
}
