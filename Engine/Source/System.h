#include <set>
#include "Entity.h"
#pragma once


class System
{
public:
	std::set<Entity> m_Entities;
	virtual ~System() {};

	/*
	ANY SYSTEM MADE SHOULD GO IN THE FOLLOWING ORDER
	1) Init
	2) LateInit
	3) Update
	4) LateUpdate
	5) PreRender
	6) Render
	7) PostRender
	*/
};

