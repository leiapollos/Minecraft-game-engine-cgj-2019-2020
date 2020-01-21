#ifndef TEXTURE_H
#define TEXTURE_H

#include "Utils/NonCopyable.h"
#include <SFML/Graphics.hpp>
#include <GL/glew.h>

class BasicTexture : public NonCopyable {
  public:
    BasicTexture() = default;
    BasicTexture(const std::string &file);

    ~BasicTexture();

    void loadFromImage(const sf::Image &image);
    void loadFromFile(const std::string &file);

    void bindTexture() const;
    void unbindTexture() const;

  private:
    GLuint m_id;
};

#endif // TEXTURE_H