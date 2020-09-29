#pragma once

#include "GameObject.hpp"
#include "Collider.hpp"

namespace shp
{
    class PrisonButton : public GameObject
    {
        public: 
            PrisonButton(ObjectProperties* props)
                : GameObject(props),
                  m_Collider(nullptr),
                  m_Pushed(false)
            {
                m_Collider = new Collider(props->transform, props->width, props->height, props->depth);
            }

            virtual void Draw() override;
            virtual void Update(double dt) override;
            virtual void Clean() override;

        protected:
            Collider* m_Collider;
            bool m_Pushed;
    };
};