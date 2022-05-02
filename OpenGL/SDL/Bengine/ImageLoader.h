#pragma once
#include <string>
#include"GLTexture.h"
#include "picoPNG.h"

class ImageLoader {
	ImageLoader() = delete;
	~ImageLoader() = delete;

	

public:
	static GLTexture loadPNG(const std::string filePath);
};

