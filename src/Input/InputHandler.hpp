#pragma once

#include <SDL.h>

namespace shp
{
    // Singleton Class for handling input
    class InputHandler
    {
        public: 
            inline static InputHandler* GetInstance(){
                return s_Instance = (s_Instance == nullptr ? new InputHandler() : s_Instance);
            }

            void Listen();
            bool GetKeyDown(SDL_Scancode key);

        private:
            InputHandler();
            void KeyUp();
            void KeyDown();

            const Uint8* m_KeyStates;
            static InputHandler* s_Instance;
    };
};