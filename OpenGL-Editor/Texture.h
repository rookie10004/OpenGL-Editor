#pragma once

class Texture
{
private:
	int width;
	int height;
	int numberColorChannel;

	unsigned char* bytes;

public:
	void Import(const char* path);
	void Initialize();
};

