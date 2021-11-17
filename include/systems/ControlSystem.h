#ifndef CONTROL_SYSTEM_H
#define CONTROL_SYSTEM_H

#include <SDL2/SDL.h>
#include "systems/System.h"

namespace ecs
{
    namespace system
    {
        class ControlSystem : public System
        {
        public:

            ControlSystem() : m_exit{ false } {}

            void processEvents()
            {
                SDL_Event e;
                while(SDL_PollEvent(&e) != 0)
                {
                    if(e.type == SDL_QUIT)
                    {
                        m_exit = true;
                    }
                }
            }

            void update(float t_delta)
            {
                Uint8 const * keystate = SDL_GetKeyboardState(NULL);
                float standardSpeed = 100.0f;

                for (Entity const & entity : m_entities)
                {
                    Coordinator & coord = *Coordinator::getInstance();
                    auto & position = coord.getComponent<ecs::component::Position>(entity);

                    if (keystate[SDL_SCANCODE_UP])
                        position.y -= standardSpeed * t_delta;
                    
                    if (keystate[SDL_SCANCODE_DOWN])
                        position.y += standardSpeed * t_delta;
                    
                    if (keystate[SDL_SCANCODE_LEFT])
                        position.x -= standardSpeed * t_delta;
                    
                    if (keystate[SDL_SCANCODE_RIGHT])
                        position.x += standardSpeed * t_delta;
                }
            }

            bool const & isExiting()
            {
                return m_exit;
            }

        private:

            bool m_exit;

        };
    }
}

#endif // !CONTROL_SYSTEM_H