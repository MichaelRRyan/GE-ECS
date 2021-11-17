#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <iostream>
#include "systems/System.h"
#include "components/Position.h"
#include "components/Health.h"
#include "components/Name.h"

namespace ecs
{
    namespace system
    {
        class RenderSystem : public System
        {
        public:

            void update(float t_delta)
            {
                for (Entity const & entity : m_entities)
                {
                    Coordinator & coord = *Coordinator::getInstance();
                    auto const & name = coord.getComponent<ecs::component::Name>(entity);
                    auto const & position = coord.getComponent<ecs::component::Position>(entity);

#ifdef RENDER_HEALTH
                    auto const & health = coord.getComponent<ecs::component::Health>(entity);
                    std::cout << name.value + " is at position " << position.x << ", " << position.y << " with health " << health.value << std::endl;
#else
                    std::cout << name.value + " is at position " << position.x << ", " << position.y << std::endl;
#endif
                }
            }

        };
    }
}

#endif // !RENDER_SYSTEM_H