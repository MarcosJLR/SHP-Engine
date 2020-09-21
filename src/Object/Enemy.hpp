#pragma once

#include "Character.hpp"
#include "Behaviour.hpp"
#include "LookWhereYoureGoing.hpp"
#include "BlendedSteering.hpp"
#include "GraphSeek.hpp"

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
                behaviour->AddBehaviour(new GraphSeek(m_Kinematic, player->GetKinematic()));
                m_Behaviour = behaviour;
            }

            virtual void Update(double dt) override;
            virtual void Draw() override;
            
        protected:
            Behaviour* m_Behaviour;
    };
};