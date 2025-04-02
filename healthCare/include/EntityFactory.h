#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include <memory>

class EntityFactory{
	public:
		virtual ~EntityFactory() = default;
		virtual std::shared_ptr<void> createEntity() const = 0;
};

#endif
