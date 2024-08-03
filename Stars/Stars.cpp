
#include "SfmlApp.h"
#include "StarsModel.h"

void PutStarsToDisplay(sf::RenderWindow &window, 
		Stars::StarsModel &starModel, 
		sf::Texture& texture);

int	main()
{
	std::string starTexture = "StarImg.png";
	sf::Texture texture;

	if (!texture.loadFromFile("./" + starTexture))
	{
		if (!texture.loadFromFile("../" + starTexture))
			printf("Texture not found %s\n", starTexture.c_str());
	}

	texture.setSmooth(true);

	SfmlGraphics::SfmlApp	application(1280, 1024, "Stars");
	Stars::StarsModel 		starsModel;
	double					baseStep = 1.0;

	return application.Run([&](double k, sf::RenderWindow &window)
	{
		starsModel.MoveStars(baseStep * k);

		PutStarsToDisplay(window, starsModel, texture);
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
		sf::Texture& texture)
{
	const auto &starList = starModel.GetStars();
	auto size = window.getView().getSize();
	double halfWidth = (double)size.x / 2.0;
	double halfHeight = (double)size.y / 2.0;
	double maxZ = std::abs(starModel.GetMaxZ());
	//printf("%d %d %d %d\n", size.x, size.y, (int)halfWidth, (int)halfHeight);

	for (auto &star : starList)
	{
		Stars::StarDescription curStar = SetPerspective(star);

		sf::Sprite sprite;
		sprite.setTexture(texture);

		double curZ = std::abs(star.z);
		double scale = 0.5 - (0.5 / maxZ) * curZ;

		sprite.setPosition({curStar.x + halfWidth, curStar.y + halfHeight});
		sprite.setScale({scale, scale});
		window.draw(sprite);
	}
}
