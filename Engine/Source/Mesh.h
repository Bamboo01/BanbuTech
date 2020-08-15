#ifndef MESH_H
#define MESH_H
#include <string>
#include <glm.hpp>
#include <vector>


using MESH_ID = uint32_t;

class Mesh
{
public:
	enum DRAW_MODE
	{
		DRAW_TRIANGLES, //default mode
		DRAW_TRIANGLE_STRIP,
		DRAW_LINES,
		DRAW_MODE_LAST,
	};
	Mesh(const std::string &meshName);
	virtual ~Mesh();

	virtual void Init();
	virtual void Render();

	const std::string name;
	DRAW_MODE mode;

	unsigned vertexArray;
	unsigned vertexBuffer;
	unsigned indexBuffer;
	unsigned indexSize;
	unsigned transformBuffer;

	bool drawInstanced;

	/*
	Instanced rendering.
	Static objects initialised once, and the matrices are never rebuffered UNLESS called.
	Dynamic objects constantly rebuffered every frame.
	*/
	std::vector<glm::mat4> StaticTransformMatrices;
	std::vector<glm::mat4> DynamicTransformMatrices;

	bool enableRender;
};

#endif