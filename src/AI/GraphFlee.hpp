#pragma once

#include "Kinematic.hpp"
#include "Seek.hpp"
#include <vector>

namespace shp
{
    class GraphFlee : public Seek
    {
        public:
            GraphFlee(Kinematic* character, 
                      double maxAcc= DEFAULT_MAXACCELERATION)
                : Seek(character, nullptr, false, maxAcc),
                  m_Targets(), m_TargetNodes(), m_CurrentNode(0)
            {}

            virtual SteeringOutput GetSteering() override;

            virtual void AddTarget(Kinematic* target);

        protected:
            std::vector<Kinematic*> m_Targets;
            std::vector<int> m_TargetNodes;
            int m_CurrentNode;

            double MinDistanceTo(int node);
            bool UpdateTargetNodes();
    };
};