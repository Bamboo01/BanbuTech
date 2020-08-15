#include <iostream>
#include <fstream>
#include <GL\glew.h>
#include <stb_image.h>
#ifndef STB_IMAGE_IMPLEMENTATION // WEEK 4
#define STB_IMAGE_IMPLEMENTATION //
#endif  
#include <stb_image.h>
#include "LoadTexture.h"

/*
//Load Texture Function
//file_path - The filename
//wrap - what type of wrapping (Default - GL_REPEAT)
*/
GLuint LoadTexture(const char* file_path, GLint wrap)				// load TGA file to memory
{
	GLubyte *	data;
	GLuint		texture = 0;
	int width, height;

	int original_no_channels;

	data = stbi_load(file_path, &width, &height, &original_no_channels, 0);
	stbi_set_flip_vertically_on_load(true);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	if (original_no_channels == 3)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	float maxAnisotropy = 1.f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, (GLint)maxAnisotropy );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
	
	glGenerateMipmap( GL_TEXTURE_2D );
	
	stbi_image_free(data);

	return texture;						
}