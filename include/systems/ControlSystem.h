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
                Uint8 const * keystate = SDL_GetKeyboardState(NULL);
                SDL_Event e;
                while(SDL_PollEvent(&e) != 0)
                {
                    if(e.type == SDL_QUIT)
                    {
                        m_exit = true;
                    }
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