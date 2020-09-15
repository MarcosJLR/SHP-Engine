#include "Engine.hpp"

using namespace shp;

int main(int argc, char** argv)
{
    Engine::GetInstance()->Init();
    
    while(Engine::GetInstance()->isRunning())
    {
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
    }

    return 0;
}