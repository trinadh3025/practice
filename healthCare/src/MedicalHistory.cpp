#include "MedicalHistory.h"
#include <iostream>

MedicalHistory::MedicalHistory(){
	previousHospital = "NA";
	doctor = std::make_shared<Doctor>(); //std::make_shared<Doctor>(nullptr);
	pastTreatment = "NA";
}
MedicalHistory::MedicalHistory(const std::string &previousHospital, std::shared_ptr<Doctor> doctor, const std::string &pastTreatment)
    : previousHospital(previousHospital), doctor(doctor), pastTreatment(pastTreatment) {}

void MedicalHistory::displayRecord() const {
    std::cout << "Previous Hospital: " << previousHospital << "\n"
              << "Doctor: " << (doctor ? doctor->id : -1) << "\n"
              << "Past Treatment: " << pastTreatment << std::endl;
}

