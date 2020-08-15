#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include <glm.hpp>

struct Light
{
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};

	//enum UNIFORM_TYPE
	//{
	//	U_LIGHT_TYPE,
	//	U_LIGHT_POSITION,
	//	U_LIGHT_COLOR,
	//	U_LIGHT_POWER,
	//	U_LIGHT_KC,
	//	U_LIGHT_KL,
	//	U_LIGHT_KQ,
	//	U_LIGHT_SPOTDIRECTION,
	//	U_LIGHT_COSCUTOFF,
	//	U_LIGHT_COSINNER,
	//	U_LIGHT_EXPONENT,
	//	U_LIGHT_ACTIVE,
	//	U_TOTAL
	//};

	LIGHT_TYPE type;
	glm::vec3 position;
	glm::vec3 color;
	float power;
	float kC;
	float kL;
	float kQ;
	glm::vec3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;
	bool active;

	//unsigned m_parameters[U_TOTAL];

	Light()
	{
		type = LIGHT_POINT;
		color = glm::vec3(1, 1, 1);
		spotDirection = glm::vec3(0, 1, 0);
		position = glm::vec3(0, 0, 0);
		power = 1.f;
		kC = 1.f;
		kL = 0.01f;
		kQ = 0.001f;
		cosCutoff = cosInner = 0.8f;
		exponent = 1.f;
		active = false;
	}
};

#endif