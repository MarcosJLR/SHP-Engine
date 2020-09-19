#pragma once

#include "Character.hpp"
#include "Behaviour.hpp"
#include "LookWhereYoureGoing.hpp"

namespace shp
{
    class Player : public Character
    {
        public:
            Player(ObjectProperties* props) : Character(props) 
            {
                m_Behaviour = new LookWhereYoureGoing(m_Kinematic);
            }

            virtual void Update(double dt) override;

        protected: 
            Behaviour* m_Behaviour;
            
    };
};