#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
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
                TTF_Init();

                // Creates the window and renderer.
                m_window = SDL_CreateWindow("Render Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN );
                
                if (m_window == nullptr)
                    printf("Window Creation Error::SDL_Error: %s\n", SDL_GetError());
                
                m_windowOpen = true;

                m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

                if (m_renderer == nullptr)
                    printf("Renderer Creation Error::SDL_Error: %s\n", SDL_GetError());
                
                // Creates the font.
                m_font = TTF_OpenFont("assets/fonts/arial.ttf", 16);

                if (m_font == nullptr)
                    printf("Open Font Error::SDL_Error: %s\n", SDL_GetError());

                // Sets up the entity rect.
                m_entityRect.w = 80.0f;
                m_entityRect.h = 80.0f;

                // Sets up the text.
                
            }

            ~RenderSystem()
            {
                SDL_DestroyTexture(m_text);

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
                SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
                SDL_RenderClear(m_renderer);

                SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

                for (Entity const & entity : m_entities)
                {
                    Coordinator & coord = *Coordinator::getInstance();
                    auto const & name = coord.getComponent<ecs::component::Name>(entity);
                    auto const & position = coord.getComponent<ecs::component::Position>(entity);

                    m_entityRect.x = position.x;
                    m_entityRect.y = position.y;
                    SDL_RenderDrawRectF(m_renderer, &m_entityRect);

                    setupText(name.value, position.x, position.y);
                    SDL_RenderCopy(m_renderer, m_text, NULL, &m_textRect);

//#define RENDER_HEALTH
#ifdef RENDER_HEALTH
                    auto const & health = coord.getComponent<ecs::component::Health>(entity);
                    setupText("Health: " + std::to_string(int(health.value)), position.x, position.y + 60.0f);
                    SDL_RenderCopy(m_renderer, m_text, NULL, &m_textRect);
#endif
                }

                SDL_RenderPresent(m_renderer);
            }

            bool isWindowOpen()
            {
                return m_windowOpen;
            }

            void setupText(std::string const & t_string, float t_x, float t_y)
            {
                SDL_Surface * setupSurface = TTF_RenderText_Solid(m_font, t_string.c_str(), SDL_Color{255,255,255});

                if (setupSurface == nullptr) 
                    printf("Text loading error::SDL_Error: %s\n", SDL_GetError());

                m_text = SDL_CreateTextureFromSurface(m_renderer, setupSurface);
                SDL_FreeSurface(setupSurface);
                SDL_QueryTexture(m_text, NULL, NULL, &m_textRect.w, &m_textRect.h);

                // Centre the text in the button.
                m_textRect.x = t_x + (m_entityRect.w / 2.0f) - (m_textRect.w / 2.0f);
                m_textRect.y = t_y + (m_entityRect.h / 2.0f) - (m_textRect.h / 2.0f);

                if (m_text == nullptr)
                    printf("Text loading error::SDL_Error: %s\n", SDL_GetError());
            }

        private:

            SDL_Window* m_window = NULL;
            SDL_Renderer* m_renderer;

            TTF_Font * m_font;
            SDL_Texture * m_text;

            SDL_FRect m_entityRect;
            SDL_Rect m_textRect;

            bool m_windowOpen;

        };
    }
}

#endif // !RENDER_SYSTEM_H