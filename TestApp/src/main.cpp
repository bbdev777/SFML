#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>

enum struct ResultCodes : int
{
    Ok = 0,
    Error = 1
};


int SfmlWindow()
{
    sf::RenderWindow window(sf::VideoMode(300, 300), "SFML works!");
    sf::CircleShape shape(20.f);
    shape.setFillColor(sf::Color::Green);

    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        shape.setPosition(window.getView().getSize().x / 2.0, window.getView().getSize().y / 2.0);
        shape.setOrigin(0, 0);
        
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}

int main(int argc, char *argv[])
{
    ResultCodes result = ResultCodes::Ok;

    SfmlWindow();
    
    return static_cast<int>(result);    
}
