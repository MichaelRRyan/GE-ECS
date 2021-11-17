#ifndef COMPONENT_ARRAY_H
#define COMPONENT_ARRAY_H

#include <array>
#include <unordered_map>
#include <assert.h>
#include "Entity.h"

// An interface is needed so that the ComponentManager can tell a generic
// ComponentArray that an entity has been destroyed and that it needs to update
// its array mappings.
class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
    virtual void entityDestroyed(Entity t_entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
public:

    void insertData(Entity t_entity, T t_component)
    {
        assert(m_entityToIndexMap.find(t_entity) == m_entityToIndexMap.end() 
            && "Component added to the same entity more than once.");
        
        // Put the new entry at the end and update the maps.
        size_t newIndex = m_size;
        m_entityToIndexMap[t_entity] = newIndex;
        m_indexToEntityMap[newIndex] = t_entity;
        m_componentArray[newIndex] = t_component;
        ++m_size;
    }

    void removeData(Entity t_entity)
    {
        assert(m_entityToIndexMap.find(t_entity) != m_entityToIndexMap.end()
            && "Removing non-existent component.");
        
        // Copies the element at the end into the deleted element's place to
        // maintain density.
        size_t indexOfRemovedEntity = m_entityToIndexMap[t_entity];
        size_t indexOfLastElement = m_size - 1;
        m_componentArray[indexOfRemovedEntity] = m_componentArray[indexOfLastElement];

        // Updates the map to point to the moved spot.
        Entity entityOfLastElement = m_indexToEntityMap[indexOfLastElement];
        m_entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        m_indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        m_entityToIndexMap.erase(t_entity);
        m_indexToEntityMap.erase(indexOfLastElement);

        --m_size;
    }

    T & getData(Entity t_entity)
    {
        assert(m_entityToIndexMap.find(t_entity) != m_entityToIndexMap.end()
            && "Retrieving non-existent component.");
        
        // Returns a reference to the entity's component.
        return m_componentArray[m_entityToIndexMap[t_entity]];
    }

    void entityDestroyed(Entity t_entity) override
    {
        if (m_entityToIndexMap.find(t_entity) != m_entityToIndexMap.end())
        {
            // Remove the entity's component if it existed.
            removeData(t_entity);
        }
    }

private:

    // The packed array of components (of generic type T), set to a specified
    // maximum amount, matching the maximum number of entities allowed to exist
    // simultaneously, so that each entity has a unique spot.
    std::array<T, MAX_ENTITIES> m_componentArray;

    // Map from an entity ID to an array index.
    std::unordered_map<Entity, size_t> m_entityToIndexMap;

    // Map from an array index to an entity ID.
    std::unordered_map<size_t, Entity> m_indexToEntityMap;

    // Total size of valid entries in the array.
    size_t m_size;

};

#endif // !COMPONENT_ARRAY_H