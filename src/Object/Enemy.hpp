#pragma once

#include "Character.hpp"
#include "Behaviour.hpp"
#include "LookWhereYoureGoing.hpp"
#include "BlendedSteering.hpp"
#include "PrioritySteering.hpp"
#include "ObstacleAvoidance.hpp"
#include "GraphSeek.hpp"
#include "GraphWander.hpp"

namespace shp
{
    class Enemy : public Character
    {
        public: 
            Enemy(ObjectProperties* props,
                  Character* player)
                : Character(props)
            {
                BlendedSteering* behaviour = new BlendedSteering();
                behaviour->AddBehaviour(new LookWhereYoureGoing(m_Kinematic));
                behaviour->AddBehaviour(new GraphWander(m_Kinematic));
                behaviour->AddBehaviour(new ObstacleAvoidance(m_Kinematic));
                m_Behaviour = behaviour;
            }

            virtual void Update(double dt) override;
            virtual void Draw() override;
            
        protected:
            Behaviour* m_Behaviour;
    };
};