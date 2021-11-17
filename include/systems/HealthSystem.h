#ifndef HEALTH_SYSTEM_H
#define HEALTH_SYSTEM_H

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include "systems/System.h"

namespace ecs
{
    namespace system
    {
        class HealthSystem : public System
        {
        public:

            void setRenderer(SDL_Renderer * t_renderer)
            {
                m_renderer = t_renderer;

                // Creates the font.
                m_font = TTF_OpenFont("assets/fonts/arial.ttf", 16);

                if (m_font == nullptr)
                    printf("Open Font Error::SDL_Error: %s\n", SDL_GetError());
            }

            void render()
            {
                SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

                float offset = 0.0f;
                for (Entity const & entity : m_entities)
                {
                    Coordinator & coord = *Coordinator::getInstance();
                    auto const & name = coord.getComponent<ecs::component::Name>(entity);
                    auto const & health = coord.getComponent<ecs::component::Health>(entity);

                    setupText(name.value + ": " + std::to_string(int(health.value)), 10.0f, 10.0f + offset++ * 16.0f);
                    SDL_RenderCopy(m_renderer, m_text, NULL, &m_textRect);
                }

            }

            void setupText(std::string const & t_string, float t_x, float t_y)
            {
                SDL_Surface * setupSurface = TTF_RenderText_Solid(m_font, t_string.c_str(), SDL_Color{255,255,255});

                if (setupSurface == nullptr) 
                    printf("Text loading error::SDL_Error: %s\n", SDL_GetError());

                m_text = SDL_CreateTextureFromSurface(m_renderer, setupSurface);
                SDL_FreeSurface(setupSurface);
                SDL_QueryTexture(m_text, NULL, NULL, &m_textRect.w, &m_textRect.h);

                // Set the text position.
                m_textRect.x = t_x;
                m_textRect.y = t_y;

                if (m_text == nullptr)
                    printf("Text loading error::SDL_Error: %s\n", SDL_GetError());
            }

        private:

            SDL_Renderer * m_renderer;

            TTF_Font * m_font;
            SDL_Texture * m_text;
            SDL_Rect m_textRect;
            
        };
    }
}

#endif // !HEALTH_SYSTEM_H