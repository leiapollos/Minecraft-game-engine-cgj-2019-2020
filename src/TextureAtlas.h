
#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

#include "BasicTexture.h"

class TextureAtlas : public BasicTexture {
  public:
    TextureAtlas(const std::string &textureFileName);
};

#endif // TEXTUREATLAS_H