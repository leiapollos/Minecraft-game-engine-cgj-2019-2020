#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#if _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif // _WIN32

class ScreenShot
{
public:
    ScreenShot();
    ScreenShot(std::string* _filepath, std::string* _filename);
    bool createScreenShot();
private:
    std::string filepath;
    std::string filename;
    bool saveScreenShot(int width, int height, char* data);
    bool createFilePath();
    void flipV(int width, int height, char* data);
};

