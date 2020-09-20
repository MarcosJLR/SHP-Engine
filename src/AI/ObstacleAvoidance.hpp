#pragma once

#include "Kinematic.hpp"
#include "Behaviour.hpp"
#include "Seek.hpp"

namespace shp
{
    class ObstacleAvoidance : public Seek
    {
        public:
            ObstacleAvoidance(Kinematic* character, 
                              double avoidDist = DEFAULT_AVOID_DISTANCE,
                              double longLook = DEFAULT_LONG_LOOKAHEAD,
                              double shortLook = DEFAULT_SHORT_LOOKAHEAD,
                              double whiskerAngle = DEFAULT_WHISKER_ANGLE,
                              double maxAcc = 10 * DEFAULT_MAXACCELERATION)
                : Seek(character, nullptr, false, maxAcc),
                  m_AvoidDistance(avoidDist),
                  m_LongLookahead(longLook),
                  m_ShortLookahead(shortLook),
                  m_WhiskerAngle(whiskerAngle)
            {}

            virtual SteeringOutput GetSteering() override;
        
        protected:
            double m_AvoidDistance;
            double m_LongLookahead;
            double m_ShortLookahead;
            double m_WhiskerAngle;

            constexpr const static double DEFAULT_AVOID_DISTANCE = 30.0;
            constexpr const static double DEFAULT_LONG_LOOKAHEAD = 50.0;
            constexpr const static double DEFAULT_SHORT_LOOKAHEAD = 30.0;
            constexpr const static double DEFAULT_WHISKER_ANGLE = M_PI / 6.0;
    };
};