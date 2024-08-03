#pragma once

#include <memory.h>
#include <signal.h>
#include <functional>
#include <chrono>
#include <atomic>

#include <SFML/Graphics.hpp>

namespace SfmlGraphics
{
    size_t SetSigTerm(std::function<void()> handler);
    void RemoveSigTerm(size_t id);

    class SfmlApp
    {
        size_t terminationId = 0;
        std::atomic_bool run = true;

    public:
        SfmlApp(int windowWidth, 
                int windowHeight, 
                const std::string& title) : 
                    window(sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), title))
        {
            terminationId = SetSigTerm([this]()
                                       { run = false; });
        }

        int Run(std::function<void(double interFrameCoefficient, sf::RenderWindow &window)> onFrame, 
                int delayMs = 10, 
                bool clearScreen = true)
        {
            double k = 1.0;
          
            while (window.isOpen())
            {              
                ProcessEvents();
                                     
                std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();

                if (clearScreen)
                    window.clear();

                onFrame(k, window);

                window.display();

                usleep(delayMs * 1000);
                std::chrono::time_point<std::chrono::system_clock> endTime = std::chrono::system_clock::now();
                std::chrono::duration<double> delta = endTime - startTime;

                k = delta.count() / (1.0 / 60.0);
            }
            
            return 0;
        }

        virtual ~SfmlApp()
        {
            RemoveSigTerm(terminationId);
        }

    protected:
        
        void    ProcessEvents()
        {
                sf::Event event;

                if (!run)
                    window.close();

                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

        }

        sf::RenderWindow window;
    };
}
