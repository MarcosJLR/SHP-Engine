#pragma once

#include "Kinematic.hpp"
#include "Behaviour.hpp"

#include <vector> 

namespace shp
{
    class PrioritySteering : public Behaviour
    {
        public:
            PrioritySteering() 
                : m_Behaviours() 
            {}

            virtual SteeringOutput GetSteering() override;

            virtual void AddBehaviour(Behaviour* behaviour)
            {
                m_Behaviours.push_back(behaviour);
            }
        
        protected:
            std::vector<Behaviour*> m_Behaviours;
    };
};