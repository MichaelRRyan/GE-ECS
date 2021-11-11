#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <queue>
#include <array>
#include <cassert>
#include "entities/Entity.h"
#include "Signature.h"

class EntityManager
{
public:
    
    EntityManager()
    {
        // Initialises the queue with all possible entity IDs.
        for (Entity entity = 0; entity < MAX_ENTITIES; entity++)
            m_availableEntities.push(entity);
    }

    Entity createEntity()
    {
        assert(m_livingEntitiesCount < MAX_ENTITIES && "Too many entities in existence.");

        // Take an ID from the front of the queue.
        Entity id = m_availableEntities.front();
        m_availableEntities.pop();
        ++m_livingEntitiesCount;

        return id;
    }

private:

    // A queue of unused entity IDs for assigning.
    std::queue<Entity> m_availableEntities;

    // An array of signatures, each corresponding to an entity ID. 
    std::array<Signature, MAX_ENTITIES> m_signatures;

    // A count on the number of living entities, used to limit the number in existence.
    uint32_t m_livingEntitiesCount;
};

#endif // !ENTITY_MANAGER_H