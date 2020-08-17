#include "GL\glew.h"
#include "Vertex.h"
#include "LoadTexture.h"
#include "LoadTGA.h"

#ifndef MATERIAL_H
#define MATERIAL_H
#define MAX_TEXTURES 8

struct Material
{
	glm::vec3 kColor;
	glm::vec3 kAmbient;
	glm::vec3 kDiffuse;
	glm::vec3 kSpecular;
	float kShininess;

	unsigned colorTexture[MAX_TEXTURES];
	unsigned numTexture;

	unsigned specularMap;
	bool specularMapEnabled;	

	bool lightEnabled;

	Material()
	{
		//some default values
		kAmbient = glm::vec3(0.1f, 0.1f, 0.1f);
		kDiffuse = glm::vec3(0.6f, 0.6f, 0.6f);
		kSpecular = glm::vec3(0.3f, 0.3f, 0.3f);
		kColor = glm::vec3(1.f, 1.f, 1.f);
		kShininess = 5.f;
		lightEnabled = false;
		specularMapEnabled = false;
		numTexture = 0;
	}

	~Material()
	{
		for (int i = 0; i < MAX_TEXTURES; ++i)
		{
			glDeleteTextures(i, &colorTexture[i]);
		}
	}

	void AssignTexture(const char* file_path)
	{
		if (numTexture == 8)
		{
			return;
		}
		colorTexture[numTexture] = LoadTGA(file_path);
		numTexture++;
	}

	void AssignSpecularMap(const char* file_path)
	{
		if (specularMapEnabled == true)
		{
			glDeleteTextures(1, &specularMap);
		}
		specularMap = LoadTGA(file_path);
		specularMapEnabled = true;
	}
};

#endif