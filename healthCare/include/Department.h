#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "Doctor.h"
#include <string>
#include <vector>
#include <memory>

class Department {
public:
    std::string name;
    std::vector<std::shared_ptr<Doctor>> doctors;

    Department(const std::string &name);
    void addDoctor(std::shared_ptr<Doctor> doctor);
    void saveToJSON(const std::string &fileName);
    static std::vector<std::shared_ptr<Department>> loadFromJSON(const std::string &fileName);
};

#endif

