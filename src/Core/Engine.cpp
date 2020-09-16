#include "Engine.hpp"

#include <iostream>
#include "Timer.hpp"
#include "InputHandler.hpp"

namespace shp
{
    Engine* Engine::s_Instance = nullptr;

    bool Engine::Init(){
        int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
        if(SDL_Init(SDL_INIT_VIDEO) != 0 || !(IMG_Init(imgFlags) & imgFlags)){
            SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
            return false;
        }

        m_Window = SDL_CreateWindow("SHP", 
                                    SDL_WINDOWPOS_CENTERED, 
                                    SDL_WINDOWPOS_CENTERED, 
                                    SCREEN_WIDTH, 
                                    SCREEN_HEIGHT, 
                                    0); 
        if(m_Window == nullptr){
            SDL_Log("Failed to create window: %s", SDL_GetError());
            return false;
        }

        m_Renderer = SDL_CreateRenderer(m_Window, -1,
                                        SDL_RENDERER_ACCELERATED |
                                        SDL_RENDERER_PRESENTVSYNC);
        if(m_Renderer == nullptr){
            SDL_Log("Failed to create renderer: %s", SDL_GetError());
            return false;
        }

        return m_isRunning = true;
    }

    void Engine::Clean(){
        SDL_DestroyRenderer(m_Renderer);
        SDL_DestroyWindow(m_Window);

        SDL_Quit();
        IMG_Quit();
    }

    void Engine::Quit(){
        m_isRunning = false;
    }

    void Engine::Events(){
        InputHandler::GetInstance()->Listen();
    }

    void Engine::Update(){
        std::cout << Timer::GetInstance()->GetDeltaTime() << std::endl;
    }

    void Engine::Render(){

    }
};