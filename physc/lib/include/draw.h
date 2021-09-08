#include "render.h"

#pragma once

class Drawing final {
public:
    void blit(Context* context, SDL_Texture* texture, int x, int y);

    void loadTextureAndBlit(Context* context, const char* path, int x, int y);

    // not really random
    SDL_Point* randomTriangleData();
};




