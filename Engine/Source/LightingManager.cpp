#include "LightingManager.h"

void LightingManager::InitLights(std::vector<Shader*> shaders)
{
	/*Assignment of uniform blocks*/
	for (auto shader : shaders)
	{
		unsigned uniformblockLight = shader->getUniformBlock("LightBlock");
		shader->bindUniformBlock(uniformblockLight, 1);
	}

	glGenBuffers(1, &LightUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, LightUBO);
	glBufferData(GL_UNIFORM_BUFFER, (MAX_LIGHTS * sizeof(Light)) + sizeof(int), NULL, GL_STATIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, 1, LightUBO, 0, (MAX_LIGHTS * sizeof(Light)) + sizeof(int));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void LightingManager::BufferLights()
{
	glBindBuffer(GL_UNIFORM_BUFFER, LightUBO);
	glBufferData(GL_UNIFORM_BUFFER, MAX_LIGHTS * sizeof(Light), NULL, GL_STATIC_DRAW);
	std::vector<Light> activelights;
	for (auto light : lights)
	{
		activelights.push_back(light.second);
	}
	glBufferSubData(GL_UNIFORM_BUFFER, 0, activelights.size() * sizeof(Light), &activelights);
	glBufferSubData(GL_UNIFORM_BUFFER, MAX_LIGHTS * sizeof(Light), sizeof(int), &numLights);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

LightingManager::LightingManager()
{
	numLights = 0;
	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		availableLightIDs.push(i);
	}
}

LightingManager::~LightingManager()
{
}

unsigned LightingManager::getNewLightID()
{
	if (numLights == MAX_LIGHTS)
	{
		std::cout << "Max lights reached! Returning ID of the last light in the light list!" << std::endl;
		return MAX_LIGHTS - 1;
	}
	unsigned ID = availableLightIDs.front();
	availableLightIDs.pop();
	lights.insert({ ID, Light() });
	numLights++;
	return ID;
}

void LightingManager::returnLightByID(unsigned ID)
{
	if (ID > MAX_LIGHTS - 1)
	{
		std::cout << "Trying to return an invalid light!" << std::endl;
		return;
	}
	lights.erase(ID);
	availableLightIDs.push(ID);
	numLights--;
}

Light LightingManager::getLightByID(unsigned ID)
{
	assert(ID < MAX_LIGHTS, "Trying to get an invalid light ID!");
	return lights.at(ID);
}
