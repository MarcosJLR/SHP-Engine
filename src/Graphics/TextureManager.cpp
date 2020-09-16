#include "TextureManager.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include "Engine.hpp"

namespace shp
{
    TextureManager* TextureManager::s_Instance = nullptr;

    bool TextureManager::Load(std::string id, std::string filename) 
    {
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if(surface == nullptr){
            SDL_Log("Failed to load image %s: %s", filename.c_str(), SDL_GetError());
            return false;
        }

        SDL_Texture* texture = 
            SDL_CreateTextureFromSurface(
                Engine::GetInstance()->GetRenderer(), 
                surface);
        if(texture == nullptr){
            SDL_Log("Failed to texture from surface: %s", SDL_GetError());
            return false;
        }

        m_TextureMap[id] = texture;
        return true;
    }

    void TextureManager::Draw(std::string id, 
                              int x, int y, 
                              int width, int height, 
                              double angle, double scaleFactor,
                              int row, int column,
                              SDL_Point* center, SDL_RendererFlip flip)
    {
        SDL_Rect srcRect = {column * width, row * height, width, height};
        SDL_Rect dstRect = {x, y, width, height};
        SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(),
                         m_TextureMap[id],
                         &srcRect, &dstRect,
                         angle, center, flip);
    }

    void TextureManager::Drop(std::string id)
    {
        SDL_DestroyTexture(m_TextureMap[id]);
        m_TextureMap.erase(id);
    }

    void TextureManager::Clean()
    {
        for(auto& [id, texture] : m_TextureMap){
            SDL_DestroyTexture(texture);
        }
        m_TextureMap.clear();
    }
};