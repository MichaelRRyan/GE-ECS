#ifndef AI_SYSTEM_H
#define AI_SYSTEM_H

#include "systems/System.h"
#include "components/Position.h"
#include "components/Health.h"

namespace ecs
{
    namespace system
    {
        class AISystem : public System
        {
        public:

            void update(float t_delta)
            {
                for (Entity const & entity : m_entities)
                {
                    Coordinator & coord = *Coordinator::getInstance();
                    auto & position = coord.getComponent<ecs::component::Position>(entity);
                    auto & ai = coord.getComponent<ecs::component::AI>(entity);
                    auto const & health = coord.getComponent<ecs::component::Health>(entity);

                    // Change velocity.
                    ai.velocityX += static_cast<float>(rand() % 3 - 1);
                    ai.velocityY += static_cast<float>(rand() % 3 - 1);

                    // Clamp velocity to max speed.
                    float magnitude = sqrt(ai.velocityX * ai.velocityX + ai.velocityY * ai.velocityY);
                    if (magnitude > ai.maxSpeed)
                    {
                        ai.velocityX = ai.velocityX / magnitude * ai.maxSpeed;
                        ai.velocityY = ai.velocityY / magnitude * ai.maxSpeed;
                    }

                    // Apply velocity to position.
                    position.x += ai.velocityX * t_delta;
                    position.y += ai.velocityY * t_delta;

                    // Clamp to window size.
                    position.x = std::max(0.0f, position.x);
                    position.x = std::min(720.0f, position.x);
                    position.y = std::max(0.0f, position.y);
                    position.y = std::min(520.0f, position.y);
                }
            }

        };
    }
}

#endif // !AI_SYSTEM_H