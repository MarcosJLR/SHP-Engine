#include "Player.hpp"

#include "InputHandler.hpp"
#include <iostream>

namespace shp
{
    void Player::Update(double dt)
    {
        SteeringOutput steering;

        if(InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
            steering.linear -= DEFAULT_MAXACCELERATION * Vector3::X;
        if(InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
            steering.linear += DEFAULT_MAXACCELERATION * Vector3::X;
        if(InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
            steering.linear += DEFAULT_MAXACCELERATION * Vector3::Z;
        if(InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_W))
            steering.linear -= DEFAULT_MAXACCELERATION * Vector3::Z;
        if(InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_Q))
            steering.angular -= DEFAULT_MAXANGULAR;
        if(InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_E))
            steering.angular += DEFAULT_MAXANGULAR;

        m_Kinematic.Update(steering, dt);
        Character::Update(dt);
    }
};