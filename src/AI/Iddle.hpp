#pragma once

#include "Behaviour.hpp"

namespace shp
{
    class Iddle : public Behaviour
    {
        public:
            Iddle() {}

            virtual SteeringOutput GetSteering() override
            {
                SteeringOutput result;
                result.linear = Vector3::ZEROV;
                result.angular = DEFAULT_MAXANGULAR;
                return result;
            }
    };
};