#include "Department.h"
#include <json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

Department::Department(const std::string &name) : name(name){}

void Department::addDoctor(std::shared_ptr<Doctor> doctor){
	doctors.push_back(doctor);
}

void Department::saveToJSON(const std::string &fileName){
	json j;
	j["name"] = name;
	json doctorArray = json::array();
	for(const auto &doctor : doctors){
		doctorArray.push_back(doctor->id);
	}

	j["doctors"] = doctorArray;

	std::ofstream file(fileName, std::ios::app);
	file << j.dump() << std::endl;
	file.close();
}

std::vector<std::shared_ptr<Department>> Department::loadFromJSON(const std::string &fileName){
	std::vector<std::shared_ptr<Department>> departments;
	std::ifstream file(fileName);
	if(file.is_open()){
		std::string line;
		while(std::getline(file,line)){
			json j = json::parse(line);
			auto department = std::make_shared<Department>(j["name"]);
			departments.push_back(department);
		}
		file.close();
	
	}
	return departments;
}
