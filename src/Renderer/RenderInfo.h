#ifndef RENDERINFO_H
#define RENDERINFO_H

struct RenderInfo {
    GLuint vao = 0;
    GLuint indicesCount = 0;

    inline void reset() {
        vao = 0;
        indicesCount = 0;
    }
};

#endif