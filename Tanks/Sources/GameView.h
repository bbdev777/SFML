
#pragma once

#include <math.h>
#include <vector>
#include <string>
#include <random>
#include <SFML/Graphics.hpp>

namespace Tanks
{

    class GameView
    {
        std::string resourcesPath;
        std::vector<sf::Texture> textures;

        sf::Vector2u modelSize{41, 41};

    public:
        GameView(std::string resourcesPath) : resourcesPath(resourcesPath)
        {
            textures.emplace_back(LoadTexture(resourcesPath + "/TankSpritesSmall.png"));
        }

        const std::vector<sf::Texture> &GetTextures() const
        {
            return textures;
        }

        sf::Vector2u     GetModelSize() const
        {
            return modelSize;
        }
    protected:
        sf::Texture LoadTexture(std::string textureName)
        {
            sf::Texture texture;

            if (!texture.loadFromFile("./" + textureName))
            {
                texture.loadFromFile("../" + textureName);
            }

            texture.setSmooth(true);

            return texture;
        }
    };
}
