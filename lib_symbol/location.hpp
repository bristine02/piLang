#pragma once

class Location
{
    public:
        float x;
        float y;
        int16_t rot;

    public:
        Location(){};
        Location(float x, float y, int16_t rot): x(x), y(y), rot(rot){};
        ~Location(){};

};