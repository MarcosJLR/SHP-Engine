#include "Engine.hpp"

#include <iostream>
#include "Timer.hpp"
#include "InputHandler.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Graph.hpp"
#include "PrisonButton.hpp"
#include "FranMachine.hpp"
#include "JuanMachine.hpp"
#include "GreenMachine.hpp"
#include "RedMachine.hpp"
#include "NicoMachine.hpp"
#include "ExitDoor.hpp"
#include "PapiCup.hpp"

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

        TextureManager::GetInstance()->Load("nico", "assets/img/Nico.png");
        TextureManager::GetInstance()->Load("nico-escort", "assets/img/NicoLove.png");
        TextureManager::GetInstance()->Load("nico-flee", "assets/img/NicoScared.png");
        TextureManager::GetInstance()->Load("nico-dead", "assets/img/NicoWasted.png");
        TextureManager::GetInstance()->Load("juan", "assets/img/Juan.png");
        TextureManager::GetInstance()->Load("juan-mad", "assets/img/JuanMadKing.png");
        TextureManager::GetInstance()->Load("fran-locked", "assets/img/FranMolestico.png");
        TextureManager::GetInstance()->Load("fran-free", "assets/img/Fran.png");
        TextureManager::GetInstance()->Load("fran-flee", "assets/img/FranScared.png");
        TextureManager::GetInstance()->Load("fran-nico", "assets/img/FranLove.png");
        TextureManager::GetInstance()->Load("red", "assets/img/Red.png");
        TextureManager::GetInstance()->Load("red-changed", "assets/img/RedChanged.png");
        TextureManager::GetInstance()->Load("green", "assets/img/Green.png");
        TextureManager::GetInstance()->Load("green-changed", "assets/img/GreenChanged.png");
        TextureManager::GetInstance()->Load("button-pushed", "assets/img/GreenButton.png");
        TextureManager::GetInstance()->Load("button-unpushed", "assets/img/RedButton.png");
        TextureManager::GetInstance()->Load("exit-door", "assets/img/Exit.png");
        TextureManager::GetInstance()->Load("papi-cup", "assets/img/TazaPapi16.png");
        TextureManager::GetInstance()->Load("win-msg", "assets/img/NicoWins.png");
        TextureManager::GetInstance()->Load("lose-msg", "assets/img/NicoLoses.png");

        m_ChangTimeLeft = CHANG_TIME;
        m_ChangRecharge = -1.0;
        m_ChangActive = false;

        m_ButtonPushed = false;
        m_ButtonPosition = new Kinematic({944, 0, 416}, 0.0, 0.0, 0.0);
        m_ZonePosition = new Kinematic({64, 0, 64}, 0.0, 0.0, 0.0);

        m_NicoDead = false;

        PrisonButton* button = new PrisonButton(new ObjectProperties({944, 0, 416}, 32, 32, 32, "button-unpushed"));
        ExitDoor* exit = new ExitDoor(new ObjectProperties({64, 0, 64}, 64, 64, 64, "exit-door"));

        m_PapiCup = new PapiCup(new ObjectProperties({1150, 0, 64}, 16, 16, 16, "papi-cup"));

        m_Nico = new StateCharacter(new ObjectProperties({100, 5, 100}, 32, 32, 32, "nico"), nullptr);
        m_Fran = new StateCharacter(new ObjectProperties({480, 5, 480}, 32, 32, 32, "fran-locked"), nullptr);
        m_Juan = new StateCharacter(new ObjectProperties({1150, 5, 64}, 32, 32, 32, "juan"), nullptr);
        m_Red = new StateCharacter(new ObjectProperties({1150, 5, 768}, 32, 32, 32, "red"), nullptr);
        m_Green = new StateCharacter(new ObjectProperties({100, 5, 768}, 32, 32, 32, "green"), nullptr);

        m_Nico->SetMachine(new NicoMachine());
        m_Fran->SetMachine(new FranMachine());
        m_Juan->SetMachine(new JuanMachine());
        m_Red->SetMachine(new RedMachine());
        m_Green->SetMachine(new GreenMachine());

        m_GameObjects.push_back(button);
        m_GameObjects.push_back(exit);
        m_GameObjects.push_back(m_Nico);
        m_GameObjects.push_back(m_Juan);
        m_GameObjects.push_back(m_Fran);
        m_GameObjects.push_back(m_Red);
        m_GameObjects.push_back(m_Green);
        m_GameObjects.push_back(m_PapiCup);

        while(!InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE))
        {
            Events();
        }

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

    void Engine::UpdateChang(double dt)
    {
        if(m_ChangActive) 
        { 
            m_ChangTimeLeft -= dt; 
            if(m_ChangTimeLeft < 0.0)
            {
                m_ChangRecharge = CHANG_RECHARGE;
                m_ChangActive = false;
            } 
        }

        if(m_ChangRecharge >= 0.0)
        {
            m_ChangRecharge -= dt;
            if(m_ChangRecharge < 0.0)
            {
                m_ChangTimeLeft = CHANG_TIME;
            }
        }
    }

    void Engine::Update(){
        double dt = Timer::GetInstance()->GetDeltaTime();
        
        UpdateChang(dt);

        for(GameObject* object : m_GameObjects)
            object->Update(dt);
    }

    void Engine::Render()
    {
        SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(m_Renderer);

        if(m_ChangActive) 
        { 
            int rb = round(0xFF * (m_ChangTimeLeft / CHANG_TIME));
            SDL_SetRenderDrawColor(m_Renderer, 0xFF - rb, 0xFF, 0xFF - rb, 0xFF); 
            SDL_RenderClear(m_Renderer);
        }

        Graph::GetInstance()->Draw();
        
        for(GameObject* object : m_GameObjects)
            object->Draw();

        SDL_RenderPresent(m_Renderer);
    }

    void Engine::Win()
    {
        SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(m_Renderer);

        TextureManager::GetInstance()->Draw("win-msg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

        SDL_RenderPresent(m_Renderer);

        while(!InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE))
        {
            InputHandler::GetInstance()->Listen();
        }

        Quit();
    }

    void Engine::Lose()
    {
        SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(m_Renderer);

        TextureManager::GetInstance()->Draw("lose-msg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

        SDL_RenderPresent(m_Renderer);

        while(!InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE))
        {
            InputHandler::GetInstance()->Listen();
        }

        Quit();
    }
};