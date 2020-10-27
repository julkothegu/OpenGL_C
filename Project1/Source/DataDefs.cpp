#include "DataDefs.h"

std::array<Def2, 8> createCube(float x1, float y1, float z1, float a1, float a2, float size)
{
    float x = x1;
    float y = y1;
    float z = z1;

    Def2 v0, v1, v2, v3, v4, v5, v6, v7;

    do
    {
        v0.position = { x - size, y - size, z - size };
        v0.texPos = { 1.0, 0.0 };

        v1.position = { x + size, y - size, z - size };
        v0.texPos = { 1.0, 0.0 };

        v2.position = { x + size, y - size, z + size };
        v0.texPos = { 1.0, 0.0 };

        v3.position = { x - size, y - size, z + size };
        v0.texPos = { 1.0, 0.0 };

        v4.position = { x - size, y + size, z - size };
        v0.texPos = { 0.0, 0.0 };

        v5.position = { x + size, y + size, z - size };
        v0.texPos = { 0.0, 0.0 };

        v6.position = { x + size, y + size, z + size };
        v0.texPos = { 0.0, 0.0 };

        v7.position = { x - size, y + size, z + size };
        v0.texPos = { 0.0, 0.0 };

    } while (false);

    return { v0, v1, v2, v3, v4, v5, v6, v7 };
}