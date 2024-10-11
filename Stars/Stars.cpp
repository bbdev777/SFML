
#include "SfmlApp.h"
#include "StarsModel.h"

#include <vector>

void PutStarsToDisplay(sf::RenderWindow &window, 
		Stars::StarsModel &starModel, 
		std::vector<sf::Texture>& texture);


sf::Texture	LoadTexture (std::string textureName)
{
	sf::Texture texture;

	if (!texture.loadFromFile("./" + textureName))
	{
		texture.loadFromFile("../" + textureName);
	}

	texture.setSmooth(true);

	return texture;
}

int	main()
{
	SfmlGraphics::SfmlApp	application(1280, 768, "Stars");
	Stars::StarsModel 		starsModel;
	double					baseStep = 1.5;
	std::vector<sf::Texture>	textures;

	textures.emplace_back(LoadTexture("Images/StarWhite.png"));
	textures.emplace_back(LoadTexture("Images/StarRed.png"));
	textures.emplace_back(LoadTexture("Images/StarBlue.png"));
	textures.emplace_back(LoadTexture("Images/Clouds/Cloud1.png"));
	textures.emplace_back(LoadTexture("Images/Clouds/Cloud2.png"));
	textures.emplace_back(LoadTexture("Images/Clouds/Cloud3.png"));

	return application.Run([&](double k, sf::RenderWindow &window)
	{
		starsModel.MoveStars(baseStep * k);

		PutStarsToDisplay(window, starsModel, textures);
	});
}

Stars::ObjectDescription SetPerspective(const Stars::ObjectDescription &star)
{
	Stars::ObjectDescription perspectStar = star;
	double z = perspectStar.z;

	perspectStar.x = perspectStar.x / z;
	perspectStar.y = perspectStar.y / z;

	return perspectStar;
}

void PutStarsToDisplay(sf::RenderWindow &window, 
		Stars::StarsModel &starModel, 
		std::vector<sf::Texture>& texture)
{
	const auto &starList = starModel.GetStars();
	const auto &cloudList = starModel.GetClouds();
	auto size = window.getView().getSize();
	double halfWidth = (double)size.x / 2.0;
	double halfHeight = (double)size.y / 2.0;
	double maxZ = std::abs(starModel.GetMaxZ());
	double baseScale = 1.0;
	//printf("%d %d %d %d\n", size.x, size.y, (int)halfWidth, (int)halfHeight);

	auto renderSprite = [&](
		const Stars::ObjectDescription& star,
		double scaleLimit,
		double transparencyScale)
	{
		Stars::ObjectDescription curStar = SetPerspective(star);

		sf::Sprite sprite;
		int	textureOffsetX = texture[star.type].getSize().x / 2;
		int	textureOffsetY = texture[star.type].getSize().y / 2;
		sprite.setTexture(texture[star.type]);

		double curZ = std::abs(star.z);
		double scale = baseScale - (baseScale / maxZ) * curZ;

		if (scaleLimit > 0 && scale < scaleLimit)
			scale = scaleLimit;

		double transparency = scale * transparencyScale;
		if (transparency  > 255.0)
			transparency = 255.0;

		sprite.setColor(sf::Color(255, 255, 255, transparency));
		sprite.setPosition(curStar.x + halfWidth - textureOffsetX * scale, curStar.y + halfHeight - textureOffsetY * scale);
		sprite.setScale(scale, scale);
		window.draw(sprite);
	};

	for (auto &star : starList)
	{
		renderSprite(star, 0.13, 350);
	}

	baseScale *= 0.25;
	maxZ = std::abs(starModel.GetMaxZ());
	for (auto &star : cloudList)
	{
		renderSprite(star, 0.0, 1024.0);
	}
}
