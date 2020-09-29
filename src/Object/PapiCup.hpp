#pragma once

#include "GameObject.hpp"
#include "Collider.hpp"
#include "Kinematic.hpp"

namespace shp
{
    class PapiCup : public GameObject
    {
        public:
            PapiCup(ObjectProperties* props)
                : GameObject(props),
                  m_Collider(nullptr),
                  m_Kinematic(nullptr),
                  m_IsGrounded(true)
            {
                m_Kinematic = new Kinematic(props->transform, 0.0, DEFAULT_MAXSPEED, DEFAULT_MAXROTATION);
                m_Collider = new Collider(props->transform, props->width, props->height, props->depth);
            }

            inline Collider* GetCollider() { return m_Collider; }
            inline Kinematic* GetKinematic() { return m_Kinematic; }
            inline bool IsGrounded() { return m_IsGrounded; }

            virtual void Draw() override;
            virtual void Update(double dt) override;
            virtual void Clean() override;

            virtual void ThrowCup();

        protected:
            Collider* m_Collider;
            Kinematic* m_Kinematic;
            bool m_IsGrounded;
        

    };
};