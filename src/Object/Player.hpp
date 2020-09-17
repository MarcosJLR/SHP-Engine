#pragma once

#include "Character.hpp"

namespace shp
{
    class Player : public Character
    {
        public:
            Player(ObjectProperties* props) : Character(props) {}

            virtual void Update(double dt) override;
    };
};