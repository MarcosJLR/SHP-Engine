#pragma once

#include "Kinematic.hpp"
#include "Graph.hpp"
#include "GraphSeek.hpp"

namespace shp
{
    class GraphWander : public GraphSeek
    {
        public:
            GraphWander(Kinematic* character)
                : GraphSeek(character, nullptr)
            {}

            virtual SteeringOutput GetSteering() override;
    };
};