#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <queue>
#include <array>
#include <cassert>
#include "Entity.h"
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

    void destroyEntity(Entity t_entity)
    {
        assert(t_entity < MAX_ENTITIES && "Entity out of range.");

        // Invalidates the destroyed entity's signature.
        m_signatures[t_entity].reset();

        // Puts the destroyed ID at the back of the queue.
        m_availableEntities.push(t_entity);
        --m_livingEntitiesCount;
    }

    void setSignature(Entity t_entity, Signature t_signature)
    {
        assert(t_entity < MAX_ENTITIES && "Entity out of range.");

        // Puts this entity's signature into the array.
        m_signatures[t_entity] = t_signature;
    }

    Signature getSignature(Entity t_entity)
    {
        assert(t_entity < MAX_ENTITIES && "Entity out of range.");

        // Gets this entity's signature from the array.
        return m_signatures[t_entity];
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