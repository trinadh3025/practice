#ifndef PATIENT_H
#define PATIENT_H

#include "MedicalHistory.h"
#include <string>
#include <vector>
#include <memory>

class Patient{
public:
	int id;
	std::string name;
	std::string contact;
	std::vector<MedicalHistory> medicalHistory;
	bool treatmentInProgress;

	Patient(int id, const std::string &name, const std::string &contact);
	void addMedicalRecord(const MedicalHistory &history);
	void displayHistory() const;
	void saveToJSON(const std::string &fileName);
	static std::vector<std::shared_ptr<Patient>> loadFromJSON(const std::string &fileName);
};
#endif
