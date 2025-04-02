#include "Doctor.h"
#include "DoctorPersonalInfo.h"
#include "Patient.h"
#include "Appointment.h"
#include <iostream>

int main(){
        
        std::shared_ptr<EntityFactory> doctorFactory = std::make_shared<DoctorFactory>();	
        std::shared_ptr<EntityFactory> patientFactory = std::make_shared<PatientFactory>();	
        std::shared_ptr<EntityFactory> departmentFactory = std::make_shared<DepartmentFactory>();	
	
	//Create Doctor personal info
	auto docInfo = std::make_shared<DoctorPersonalInfo>("Dr.Prasad", "9245333111", "MD - Card");
	docInfo->saveToJSON("../data/DoctorPersonalInfo.json");

	//Create Doctor
	Doctor doctor(1, "Cardiology", {"10:00 AM", "11:00 AM"}, docInfo);
	doctor.saveToJSON("../data/Doctors.json");

	//Create a Patient
	Patient patient(101, "Trinadh", "8951000123");
	MedicalHistory history;
	patient.addMedicalRecord(history);
	patient.saveToJSON("../data/Patients.json");

	//Create Appointment
	Appointment appointment(std::make_shared<Patient>(patient), std::make_shared<Doctor>(doctor),
			        "10:00 AM", "Chest pain");
	appointment.saveToJSON("../data/Appointments.json");

	//Display details
	doctor.displayDetails();
	patient.displayHistory();
	appointment.displayDetails();

	return 0;
}
