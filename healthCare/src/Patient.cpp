#include "Patient.h"
#include <json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

Patient::Patient(int id, const std::string &name,
		 const std::string &contact)
		: id(id), name(name), contact(contact), treatmentInProgress(false){}

void Patient::addMedicalRecord(const MedicalHistory &history){
	medicalHistory.push_back(history);
}

void Patient::displayHistory() const {
	std::cout << "Patient ID: " << id << "\n"
		  << "Name : " << name << std::endl;
	for(const auto &history : medicalHistory){
		history.displayRecord();
	}
}

void Patient::saveToJSON(const std::string &fileName){
	json j;
	j["id"] = id;
	j["name"] = name;
	j["contact"] = contact;
	j["treatmentInProgress"] = treatmentInProgress;

	json historyArray = json::array();
	for (const auto &history : medicalHistory) {
		json h = {{"previousHospital", history.previousHospital},
			  {"doctor", history.doctor->id},  // Save only doctor ID
			  {"pastTreatment", history.pastTreatment}};
		historyArray.push_back(h);
	}
	j["medicalHistory"] = historyArray;

	std::ofstream file(fileName, std::ios::app);
	file << j.dump() << std::endl;
	file.close();

}

std::vector<std::shared_ptr<Patient>> Patient::loadFromJSON(const std::string &fileName){
	std::vector<std::shared_ptr<Patient>> patients;
	std::ifstream file(fileName);
	if (file.is_open()) {
	std::string line;
	while (std::getline(file, line)) {
	    json j = json::parse(line);
	    auto patient = std::make_shared<Patient>(j["id"], j["name"], j["contact"]);
	    patient->treatmentInProgress = j["treatmentInProgress"];
	    for (const auto &historyJson : j["medicalHistory"]) {
		MedicalHistory history(
		    historyJson["previousHospital"],
		    nullptr,  // Placeholder for doctor; needs resolution
		    historyJson["pastTreatment"]);
		patient->addMedicalRecord(history);
	    }
	    patients.push_back(patient);
	}
	file.close();
	}
	return patients;

}
