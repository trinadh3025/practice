#include "Appointment.h"
#include <json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

Appointment::Appointment(std::shared_ptr<Patient> patient, std::shared_ptr<Doctor> doctor, const std::string &timeSlot, const std::string &symptoms)
    : patient(patient), doctor(doctor), timeSlot(timeSlot), symptoms(symptoms) {}

void Appointment::displayDetails() const {
    std::cout << "Appointment - Patient: " << patient->id << ", Doctor: " << doctor->id
              << ", Time Slot: " << timeSlot << ", Symptoms: " << symptoms << std::endl;
}

void Appointment::saveToJSON(const std::string &fileName) {
    json j = {{"patient", patient->id}, {"doctor", doctor->id}, {"timeSlot", timeSlot}, {"symptoms", symptoms}};
    std::ofstream file(fileName, std::ios::app);
    file << j.dump() << std::endl;
    file.close();
}

std::vector<std::shared_ptr<Appointment>> Appointment::loadFromJSON(const std::string &fileName) {
    std::vector<std::shared_ptr<Appointment>> appointments;
    std::ifstream file(fileName);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            json j = json::parse(line);
            // Load appointment with placeholders for patient and doctor resolution
            appointments.push_back(std::make_shared<Appointment>(nullptr, nullptr, j["timeSlot"], j["symptoms"]));
        }
        file.close();
    }
    return appointments;
}
