
#pragma once

#include <math.h>
#include <vector>
#include <random>

namespace Tanks
{

    class GameModel
    {
    public:
        GameModel()
        {
            
        }


    protected:

        // StarDescription Randomize(double defaultZ)
        // {
        //     int radiusX = std::uniform_int_distribution<int>(8500, 95000)(generator);
        //     int radiusY = radiusX;
        //     double  radians = DegToRad(double(rand() % 359));
        //     double  x = (double)(radiusX) * cos(radians);
        //     double  y = (double)(radiusY) * sin(radians);
        //     double  z = -(double)(rand() % (int)fabs(defaultZ));

        //     StarDescription description {x, y, z, std::uniform_int_distribution<int>(0, 2)(generator)};

        //     return description;
        // }

        double defaultZ = -250.0;

        std::random_device generator;
    };
}
