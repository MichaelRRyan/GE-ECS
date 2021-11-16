#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <memory>
#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"

class Coordinator
{
public:

    void init()
    {
        // Creates pointers to each manager.
		m_componentManager = std::make_unique<ComponentManager>();
		m_entityManager = std::make_unique<EntityManager>();
		m_systemManager = std::make_unique<SystemManager>();
    }

    // Entity methods.
    Entity createEntity()
    {
        return m_entityManager->createEntity();
    }

    void destroyEntity(Entity t_entity)
    {
        m_entityManager->destroyEntity(t_entity);
        m_componentManager->entityDestroyed(t_entity);
        m_systemManager->entityDestroyed(t_entity);
    }

    // Component methods.
    template<typename T>
    void registerComponent()
    {
        m_componentManager->registerComponent<T>();
    }

    template<typename T>
    void addComponent(Entity t_entity, T t_component)
    {
        m_componentManager->addComponent<T>(t_entity, t_component);

        auto signature = m_entityManager->getSignature(t_entity);
        signature.set(m_componentManager->getComponentType<T>(), true);
        m_entityManager->setSignature(t_entity, signature);

        m_systemManager->entitySignatureChanged(t_entity, signature);
    }

    template<typename T>
    T & getComponent(Entity t_entity)
    {
        return m_componentManager->getComponent<T>(t_entity);
    }

    template<typename T>
    ComponentType getComponentType()
    {
        return m_componentManager->getComponentType<T>();
    }

    // System methods.
    template<typename T>
    std::shared_ptr<T> registerSystem()
    {
        return m_systemManager->registerSystem<T>();
    }

    template<typename T>
    void setSystemSignature(Signature t_signature)
    {
        m_systemManager->setSignature<T>(Signature);
    }

private:

    std::unique_ptr<ComponentManager> m_componentManager;
    std::unique_ptr<EntityManager> m_entityManager;
    std::unique_ptr<SystemManager> m_systemManager;

};

#endif // !COORDINATOR_H