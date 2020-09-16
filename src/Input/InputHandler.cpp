#include "InputHandler.hpp"

#include "Engine.hpp"

namespace shp
{
    InputHandler* InputHandler::s_Instance = nullptr;

    InputHandler::InputHandler()
    {
        m_KeyStates = SDL_GetKeyboardState(nullptr);
    }

    void InputHandler::Listen()
    {
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            switch (event.type)
            {
                case SDL_QUIT: Engine::GetInstance()->Quit(); break;
                case SDL_KEYDOWN: KeyDown(); break;
                case SDL_KEYUP: KeyUp(); break;
                default: break;
            }
        }
    }

    bool InputHandler::GetKeyDown(SDL_Scancode key)
    {
        return m_KeyStates[key] == 1;
    }
    
    void InputHandler::KeyDown()
    {
        m_KeyStates = SDL_GetKeyboardState(nullptr);
    }
    
    void InputHandler::KeyUp()
    {
        m_KeyStates = SDL_GetKeyboardState(nullptr);
    }

};