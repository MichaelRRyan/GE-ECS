#ifndef SYSTEM_H
#define SYSTEM_H

#include <set>
#include "Entity.h"

namespace ecs
{
    namespace system
    {
        class System
        {
        public:
            std::set<Entity> m_entities;
        };
    }
}

#endif // !SYSTEM_H