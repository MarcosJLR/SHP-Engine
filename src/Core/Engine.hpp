#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "GameObject.hpp"
#include "StateCharacter.hpp"

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

            inline StateCharacter* GetNico() { return m_Nico; }
            inline StateCharacter* GetFran() { return m_Fran; }
            inline StateCharacter* GetJuan() { return m_Juan; }
            inline StateCharacter* GetRed() { return m_Red; }
            inline StateCharacter* GetGreen() { return m_Green; }

            inline void ActivateChang() { m_ChangActive = true; }
            inline bool ChangAvailable() { return m_ChangTimeLeft > 0; }
            inline bool ChangActive() { return m_ChangActive; }

            void UpdateChang(double dt);

            inline bool IsFranFree() { return m_ButtonPushed; }
            inline void FreeFran() { m_ButtonPushed = true; }
            inline void LockFran() { m_ButtonPushed = false; }
            inline Kinematic* GetButtonPosition() { return m_ButtonPosition; }
            inline Kinematic* GetZonePosition() { return m_ZonePosition; }

            inline bool IsNicoDead() { return m_NicoDead; }
            inline void KillNico() { m_NicoDead = true; }
            inline void ReviveNico() { m_NicoDead = false; }

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
            StateCharacter* m_Nico;
            StateCharacter* m_Fran;
            StateCharacter* m_Juan;
            StateCharacter* m_Red;
            StateCharacter* m_Green;

            bool m_ChangActive;
            double m_ChangTimeLeft;
            double m_ChangRecharge;

            bool m_ButtonPushed;
            Kinematic* m_ButtonPosition;

            Kinematic* m_ZonePosition;

            bool m_NicoDead; 

            const double CHANG_TIME = 500.0;
            const double CHANG_RECHARGE = 1500.0;
    };
};