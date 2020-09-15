#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>

namespace shp
{
    // Singleton class to Manage Textures
    class TextureManager
    {
        public:
            static TextureManager* GetInstance(){
                return s_Instance == nullptr ? new TextureManager() : s_Instance;
            }

            bool Load(std::string id, std::string filename);
            void Draw(std::string id, 
                      int x, int y, 
                      int width, int height, 
                      double angle = 0.0, double scaleFactor = 1.0,
                      int row = 0, int column = 0,
                      SDL_Point* center = nullptr, 
                      SDL_RendererFlip flip = SDL_FLIP_NONE);
            void Drop(std::string id);
            void Clean();

        private:
            TextureManager() {}
            std::map<std::string, SDL_Texture*> m_TextureMap;
            static s_Instance{nullptr};
    };
};