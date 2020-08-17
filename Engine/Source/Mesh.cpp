#include "Mesh.h"
#include "GL\glew.h"
#include "Vertex.h"


Mesh::Mesh(const std::string &meshName)
	: name(meshName)
	, mode(DRAW_TRIANGLES)
	, enableRender(true)
	, drawInstanced(false)
{
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

void Mesh::Init()
{
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glGenBuffers(1, &transformBuffer);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);
	glBufferData(GL_ARRAY_BUFFER, 1000 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	if (StaticTransformMatrices.size() > 0)
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, StaticTransformMatrices.size() * sizeof(glm::mat4), &StaticTransformMatrices[0]);
	}

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);
	glVertexAttribDivisor(7, 1);

	glBindVertexArray(0);
}

void Mesh::Render()
{
	if (!enableRender)
	{
		return;
	}
	glBindVertexArray(vertexArray);

	if (DynamicTransformMatrices.size() > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, StaticTransformMatrices.size() * sizeof(glm::mat4), DynamicTransformMatrices.size() * sizeof(glm::mat4), &DynamicTransformMatrices[0]);
	}
	if (mode == DRAW_LINES)
		glDrawElementsInstanced(GL_LINES, indexSize, GL_UNSIGNED_INT, 0, DynamicTransformMatrices.size());
	else if (mode == DRAW_TRIANGLE_STRIP)
		glDrawElementsInstanced(GL_TRIANGLE_STRIP, indexSize, GL_UNSIGNED_INT, 0, DynamicTransformMatrices.size());
	else
		glDrawElementsInstanced(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0, DynamicTransformMatrices.size());

	glBindVertexArray(0);
}