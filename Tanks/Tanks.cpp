
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

	int	iter = 0;
	return application.Run([&](double k, sf::RenderWindow &window)
	{
		auto modelSize = view.GetModelSize();
		int	offset = 0;
		int	level = 7;
			
		if (iter % 2 == 0)
			offset ++;

		sf::Sprite sprite(textures[0], sf::IntRect(modelSize.x * offset, modelSize.y * level, modelSize.x - 1, modelSize.y - 1));
		
		window.clear();
		window.draw(sprite);

		iter++;
	});
}

