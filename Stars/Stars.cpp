
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

	return application.Run([&](double k, sf::RenderWindow &window)
	{
		starsModel.MoveStars(baseStep * k);

		PutStarsToDisplay(window, starsModel, textures);
	});
}

Stars::StarDescription SetPerspective(const Stars::StarDescription &star)
{
	Stars::StarDescription perspectStar = star;
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
	auto size = window.getView().getSize();
	double halfWidth = (double)size.x / 2.0;
	double halfHeight = (double)size.y / 2.0;
	double maxZ = std::abs(starModel.GetMaxZ());
	double baseScale = 1.0;
	//printf("%d %d %d %d\n", size.x, size.y, (int)halfWidth, (int)halfHeight);

	for (auto &star : starList)
	{
		Stars::StarDescription curStar = SetPerspective(star);

		sf::Sprite sprite;
		sprite.setTexture(texture[star.type]);

		double curZ = std::abs(star.z);
		double scale = baseScale - (baseScale / maxZ) * curZ;

		sprite.setPosition(curStar.x + halfWidth, curStar.y + halfHeight);
		sprite.setScale(scale, scale);
		window.draw(sprite);
	}
}
