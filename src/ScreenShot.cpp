#include "ScreenShot.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
ScreenShot::ScreenShot()
{
	filepath = std::string("../screenshots/");
	filename = std::string("gamecapture.png");
	createFilePath();

}

ScreenShot::ScreenShot(std::string* _filepath, std::string* _filename)
{
	filepath = std::string(_filepath->c_str());
	filename = std::string(_filename->c_str());
	createFilePath();
}

bool ScreenShot::createScreenShot()
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	int x = viewport[0];
	int y = viewport[1];
	int width = viewport[2];
	int height = viewport[3];

	char* data = (char*)malloc((size_t)width * (size_t)height * 3); // 3 components (R, G, B)

	if (!data)
		return 0;

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

	flipV(width, height, data);
	if (!saveScreenShot(width, height, data))
		return false;

	return true;
}

bool ScreenShot::saveScreenShot(int width, int height, char* data)
{
	std::string fullPath = filepath + filename;
	int saved = stbi_write_png(fullPath.c_str(), width, height, 3, data, 0);

	free(data);

	return saved;
}

bool ScreenShot::createFilePath()
{
	#if _WIN32
	if (_mkdir(filepath.c_str()) != 0) {
		std::cout << "Error with \"" + filepath + "\" directory\n";
		return false;
	}
	#else
	if (!mkdir(filepath.c_str(), 0700)){
		std::cout << "Error with \"" + filepath + "\" directory\n";
		return false;	
	}
	#endif // _WIN32
	return true;
}

void ScreenShot::flipV(int width, int height, char* data)
{
	char rgb[3];

	for (int y = 0; y < height / 2; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			int top = (x + y * width) * 3;
			int bottom = (x + (height - y - 1) * width) * 3;

			memcpy(rgb, data + top, sizeof(rgb));
			memcpy(data + top, data + bottom, sizeof(rgb));
			memcpy(data + bottom, rgb, sizeof(rgb));
		}
	}

}
