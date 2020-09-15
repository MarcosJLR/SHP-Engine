#pragma once

#include <SDL.h>
#include <SDL_image.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960

namespace shp
{
    // Singleton class for the engine
    // Made to join everything together
    class Engine
    {
        public: 
            static Engine* GetInstance(){
                return s_Instance == nullptr ? new Engine() : s_Instance;
            }

            bool Init();
            void Clean();
            void Quit();

            void Events();
            void Update();
            void Render();

            inline bool isRunning() { return m_isRunning; }
            inline SDL_Renderer* GetRenderer() { return m_Renderer; }

        private:
            Engine() : m_isRunning(false) {}

            bool m_isRunning;
            SDL_Window* m_Window;
            SDL_Renderer* m_Renderer;
            static Engine* s_Instance{nullptr};
    };
};