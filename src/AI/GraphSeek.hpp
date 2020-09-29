#pragma once

#include "Kinematic.hpp"
#include "Behaviour.hpp"
#include "Graph.hpp"
#include "Seek.hpp"

namespace shp
{
    class GraphSeek : public Seek 
    {
        public:
            GraphSeek(Kinematic* character, 
                      Kinematic* target,
                      double radius = DEFAULT_RADIUS,
                      double maxAcc = DEFAULT_MAXACCELERATION)
                : Seek(character, nullptr, false, maxAcc),
                  m_Target(target),
                  m_TargetNode(-1),
                  m_CharacterNode(-1),
                  m_Radius(radius),
                  m_Path()
            {}

            virtual SteeringOutput GetSteering() override;

            inline Path GetPath() { return m_Path; }

        protected:
            Kinematic* m_Target;
            int m_TargetNode;
            int m_CharacterNode;
            double m_Radius;
            Path m_Path;

            constexpr const static double DEFAULT_RADIUS = 50.0;
    };
};