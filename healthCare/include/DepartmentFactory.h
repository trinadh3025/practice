#ifndef DEPARTMENT_FACTORY_H
#define DEPARTMENT_FACTORY_H

#include "EntityFactory.h"
#include "Department.h"

class DepartmentFactory: public EntityFactory{
public:
	std::shared_ptr<void> createEntity() const override{
		return std::make_shared<Department>();
	}
};
#endif
