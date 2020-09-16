#pragma once

namespace shp
{
    const int TARGET_FPS = 60;
    const double TARGET_DELTATIME = 1.5;

    // Singleton class that handles time
    class Timer
    {
        public:
            inline static Timer* GetInstance(){
                return s_Instance = (s_Instance == nullptr ? new Timer() : s_Instance);
            }

            void Tick();
            inline double GetDeltaTime() { return m_DeltaTime; }

        private:
            Timer() {}
            static Timer* s_Instance;
            double m_DeltaTime;
            double m_LastTime;
    };
    
};