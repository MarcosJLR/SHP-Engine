#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "GameObject.hpp"

namespace shp
{
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 960;

    // Singleton class for the engine
    // Made to join everything together
    class Engine
    {
        public: 
            inline static Engine* GetInstance(){
                return s_Instance = (s_Instance == nullptr ? new Engine() : s_Instance);
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
            Engine() 
                : m_isRunning(false), 
                  m_Window(nullptr),
                  m_Renderer(nullptr) 
            {}

            bool m_isRunning;
            SDL_Window* m_Window;
            SDL_Renderer* m_Renderer;
            static Engine* s_Instance;

            std::vector<GameObject*> m_GameObjects;

    };
};