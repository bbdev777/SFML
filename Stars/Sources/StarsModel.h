
#pragma once

#include <math.h>
#include <vector>
#include <random>

namespace Stars
{
    struct ObjectDescription
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

            for (auto &item : cloudList)
            {
                item.z += step;

                if(item.z >= 0.0)
                {
                    item = Randomize(defaultZ, 3, 5);
                    item.z = defaultZ;
                }
            }
        }

        const std::vector<ObjectDescription> &GetStars() const
        {
            return starList;
        }

        const std::vector<ObjectDescription> &GetClouds() const
        {
            return cloudList;
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

            for (int i = 0; i < 25; i++)
            {     
                cloudList.push_back(Randomize(defaultZ, 3, 5));
            }

        }

    protected:
        double DegToRad(double x)
        {
            return x * (3.14159 / 180.0);
        }

        ObjectDescription Randomize(double defaultZ, int randomizeMin = 0, int randomizeMax = 2)
        {
            int radiusX = std::uniform_int_distribution<int>(8500, 95000)(generator);
            int radiusY = radiusX;
            double  radians = DegToRad(double(rand() % 359));
            double  x = (double)(radiusX) * cos(radians);
            double  y = (double)(radiusY) * sin(radians);
            double  z = -(double)(rand() % (int)fabs(defaultZ));

            ObjectDescription description {x, y, z, std::uniform_int_distribution<int>(randomizeMin, randomizeMax)(generator)};

            return description;
        }

        double defaultZ = -300.0;

        std::random_device generator;
        std::vector<ObjectDescription> starList;
        std::vector<ObjectDescription> cloudList;
    };
}
