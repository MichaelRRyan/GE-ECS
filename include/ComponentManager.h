#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <unordered_map>
#include <memory>
#include "components/Component.h"
#include "ComponentArray.h"

class ComponentManager
{
public:

    template<typename T>
    void registerComponent()
    {
        const char * typeName = typeid(T).name();

        assert(m_componentTypes.find(typeName) == m_componentTypes.end()
            && "Registering component type more than once.");
        
        // Adds this component type to the component type map.
        m_componentTypes.insert({ typeName, m_nextComponentType });

        // Creates a ComponentArray pointer and adds it to the component
        // arrays map.
        m_componentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

        // Increments the value so that the next component registered will be different.
        ++m_nextComponentType;
    }

    template<typename T>
    ComponentType getComponentType()
    {
        const char * typeName = typeid(T).name();

        assert(m_componentTypes.find(typeName) != m_componentTypes.end()
            && "Component not registered before use.");
        
        // Returns this component's type - used for creating signatures.
        return m_componentTypes[typeName];
    }

    template<typename T>
    void addComponent(Entity t_entity, T t_component)
    {
        // Adds the component to the array for an entity.
        getComponentArray<T>()->insertData(t_entity, t_component);
    }

    template<typename T>
    void removeComponent(Entity t_entity)
    {
        // Removes the component from the array for an entity.
        getComponentArray<T>()->removeData(t_entity);
    }

    template<typename T>
    T & getComponent(Entity t_entity)
    {
        return getComponentArray<T>()->getData(t_entity);
    }

    void entityDestroyed(Entity t_entity)
    {
        // Notifies each component array that an entity has been destroyed.
        // If it has a component for that entity, it will remove it.
        for (auto const & pair : m_componentArrays)
        {
            auto const & component = pair.second;

            component->entityDestroyed(t_entity);
        }
    }

private:

    // Map from type string pointer to a component type.
    std::unordered_map<const char *, ComponentType> m_componentTypes{};

    // Map from type string pointer to a component array.
    std::unordered_map<const char *, std::shared_ptr<IComponentArray>> m_componentArrays{};

    // The component type to be assigned to the next registered component - starting at 0.
    ComponentType m_nextComponentType{};

    // Convenience function to get the statically casted pointer to the ComponentArray of type T.
    template<typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray()
    {
        const char * typeName = typeid(T).name();

        assert(m_componentTypes.find(typeName) != m_componentTypes.end()
            && "Component not registered before use.");
        
        return std::smart_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
    }
};

#endif // !COMPONENT_MANAGER_H