#pragma once

#include <string>
#include "vector3D.hpp"

namespace shp
{
    struct ObjectProperties
    {
        public:
            ObjectProperties(Vector3 transform,
                             int width, 
                             int height,
                             int depth,
                             std::string textureID)
                : transform(transform),
                  width(width),
                  height(height),
                  depth(depth),
                  textureID(textureID)
            {}
        
            Vector3 transform;
            int width, height, depth;
            std::string textureID;
    };

    class GameObject
    {
        public:
            GameObject(ObjectProperties* props)
                : m_Transform(props->transform),
                  m_Width(props->width),
                  m_Height(props->height),
                  m_Depth(props->depth),
                  m_TextureID(props->textureID)
            {}

            virtual void Draw()=0;
            virtual void Update(double dt)=0;
            virtual void Clean()=0;

        protected:
            Vector3 m_Transform;
            int m_Width, m_Height, m_Depth;
            std::string m_TextureID;
    };
};