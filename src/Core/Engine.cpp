#include "Engine.hpp"

#include <iostream>
#include "Timer.hpp"
#include "InputHandler.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Graph.hpp"

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

        Graph::GetInstance()->Load("assets/map/Map.1");

        TextureManager::GetInstance()->Load("player", "assets/img/Player.png");
        TextureManager::GetInstance()->Load("enemy", "assets/img/Enemy.png");
        GameObject* player = new Player(new ObjectProperties({100,50,100}, 32, 32, 32, "player"));
        GameObject* enemy = new Enemy(new ObjectProperties({500,50,500}, 32, 32, 32, "enemy"), (Character*) player);

        m_GameObjects.push_back(player);
        m_GameObjects.push_back(enemy);

        return m_isRunning = true;
    }

    void Engine::Clean(){
        Graph::GetInstance()->Clean();

        for(GameObject* object : m_GameObjects)
            object->Clean();

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
        for(GameObject* object : m_GameObjects)
            object->Update(Timer::GetInstance()->GetDeltaTime());
    }

    void Engine::Render(){
        SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(m_Renderer);

        Graph::GetInstance()->Draw();
        
        for(GameObject* object : m_GameObjects)
            object->Draw();

        SDL_RenderPresent(m_Renderer);
    }
};