#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <SDL2/SDL.h>
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

            RenderSystem()
            {
                SDL_Init(SDL_INIT_EVERYTHING);

                // Creates the window and renderer.
                m_window = SDL_CreateWindow("Render Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN );
                
                if (m_window == nullptr)
                    printf("Window Creation Error::SDL_Error: %s\n", SDL_GetError());
                
                m_windowOpen = true;

                m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

                if (m_renderer == nullptr)
                    printf("Renderer Creation Error::SDL_Error: %s\n", SDL_GetError());
            }

            ~RenderSystem()
            {
                // Destroys the window.
                SDL_DestroyWindow(m_window);

                // Quits the SDL subsystems.
                SDL_Quit();
            }

            void update(float t_delta)
            {

            }

            void processEvents()
            {
                SDL_Event e;
                while(SDL_PollEvent(&e) != 0)
                {
                    if(e.type == SDL_QUIT)
                    {
                        m_windowOpen = false;
                    }
                }
            }

            void render()
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

                SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
                SDL_RenderClear(m_renderer);
                SDL_RenderPresent(m_renderer);
            }

            bool isWindowOpen()
            {
                return m_windowOpen;
            }

        private:

            SDL_Window* m_window = NULL;
            SDL_Renderer* m_renderer;
            bool m_windowOpen;

        };
    }
}

#endif // !RENDER_SYSTEM_H