#ifndef SYSTEM_H
#define SYSTEM_H

#include <set>
#include "entities/Entity.h"

class System
{
public:
    std::set<Entity> m_entities;
};

#endif // !SYSTEM_H