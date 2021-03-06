#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <unordered_map>
#include <assert.h>
#include "systems/System.h"
#include "Signature.h"

class SystemManager
{
public:

    template<typename T>
    std::shared_ptr<T> registerSystem()
    {
        const char * typeName = typeid(T).name();

        assert(m_systems.find(typeName) == m_systems.end()
            && "Registering system more than once.");
        
        // Creates a pointer to the system and returns it so it can be used externally.
        auto system = std::make_shared<T>();
        m_systems.emplace(typeName, system);
        return system;
    }

    template<typename T>
    void setSignature(Signature t_signature)
    {
        const char * typeName = typeid(T).name();

        assert(m_systems.find(typeName) != m_systems.end()
            && "System used before registered.");
        
        // Sets the signature for this system.
        m_signatures.emplace(typeName, t_signature);
    }

    void entityDestroyed(Entity t_entity)
    {
        // Erases a destroyed entity from all system lists.
        // m_entities is a set so no check is needed.
        for (auto const & pair : m_systems)
        {
            auto const & system = pair.second;

            system->m_entities.erase(t_entity);
        }
    }

    void entitySignatureChanged(Entity t_entity, Signature t_entitySignature)
    {
        // Notify each system that an entity's signature has changed.
        for (auto const & pair : m_systems)
        {
            auto const & type = pair.first;
            auto const & system = pair.second;
            auto const & systemSignature = m_signatures[type];

            // Entity signature matches system signature - insert into set.
            if ((t_entitySignature & systemSignature) == systemSignature)
                system->m_entities.insert(t_entity);

            // Entity signature does not match system signature - erase from set.
            else
                system->m_entities.erase(t_entity);
        }
    }

private:

    // Map from system type string pointer to a signature.
    std::unordered_map<const char *, Signature> m_signatures{};

    // Map from system type string pointer to a system pointer.
    std::unordered_map<const char *, std::shared_ptr<ecs::system::System>> m_systems;

};

#endif // !SYSTEM_MANAGER_H