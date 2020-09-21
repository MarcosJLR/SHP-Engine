#pragma once

#include "Behaviour.hpp"
#include "Kinematic.hpp"

#include <vector>
#include <algorithm>

namespace shp
{
    class BlendedSteering : public Behaviour
    {
        public:
            BlendedSteering(double maxAcc = DEFAULT_MAXACCELERATION,
                            double maxAngular = DEFAULT_MAXANGULAR)
                : m_WeightedBehaviours(),
                  m_MaxAcceleration(maxAcc),
                  m_MaxAngular(maxAngular)
            {}

            virtual SteeringOutput GetSteering() override;

            inline void AddBehaviour(Behaviour* behaviour, double weight = 1.0) 
            {
                m_WeightedBehaviours.push_back({behaviour, weight});
            }
            inline Behaviour* GetBehaviour(int i)
            {
                if(i < 0 || i >= (int) m_WeightedBehaviours.size())
                    return nullptr;
                return m_WeightedBehaviours[i].first;
            }


        protected:
            std::vector<std::pair<Behaviour*, double>> m_WeightedBehaviours;

            double m_MaxAcceleration;
            double m_MaxAngular;
    };
};
