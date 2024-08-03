
#pragma once

#include <math.h>
#include <vector>
#include <random>

namespace Stars
{
    struct StarDescription
    {
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
        int type = 0; // 0 - 2
    };

    class StarsModel
    {
    public:
        StarsModel()
        {
            GenerateStars();
        }

        void MoveStars(double step)
        {
            for (auto &item : starList)
            {
                item.z += step;

                if(item.z >= 0.0)
                {
                    item = Randomize(defaultZ);
                    item.z = defaultZ;
                }
            }
        }

        const std::vector<StarDescription> &GetStars() const
        {
            return starList;
        }

        double  GetMaxZ() const
        {
            return defaultZ;
        }

        void GenerateStars()
        {
            for (int i = 0; i < 500; i++)
            {               
                starList.push_back(Randomize(defaultZ));
            }
        }

    protected:
        double DegToRad(double x)
        {
            return x * (3.14159 / 180.0);
        }

        StarDescription Randomize(double defaultZ)
        {
            int radiusX = std::uniform_int_distribution<int>(8500, 95000)(generator);
            int radiusY = radiusX;
            double  radians = DegToRad(double(rand() % 359));
            double  x = (double)(radiusX) * cos(radians);
            double  y = (double)(radiusY) * sin(radians);
            double  z = -(double)(rand() % (int)fabs(defaultZ));

            StarDescription description {x, y, z, std::uniform_int_distribution<int>(0, 2)(generator)};

            return description;
        }

        double defaultZ = -250.0;

        std::random_device generator;
        std::vector<StarDescription> starList;
    };
}
