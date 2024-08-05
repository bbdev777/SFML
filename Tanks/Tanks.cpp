
#include "SfmlApp.h"
#include "GameModel.h"
#include "GameView.h"

#include <vector>


int	main()
{
	SfmlGraphics::SfmlApp	application(1280, 1024, "Tanks");
	Tanks::GameView			view("Images");
	Tanks::GameModel		model;
	double					baseStep = 1.5;

	auto&	textures = view.GetTextures();

	return application.Run([&](double k, sf::RenderWindow &window)
	{
		auto modelSize = view.GetModelSize();
		sf::Sprite sprite(textures[0], sf::IntRect(modelSize.x * 15, modelSize.y * 15, modelSize.x, modelSize.y));
		
		window.clear();
		window.draw(sprite);
	});
}

