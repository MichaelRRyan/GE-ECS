#ifndef AI_COMPONENT_H
#define AI_COMPONENT_H

namespace ecs
{
    namespace component
    {
        struct AI
        {
            float velocityX;
            float velocityY;
            float maxSpeed;
        };
    }
}

#endif // !AI_COMPONENT_H