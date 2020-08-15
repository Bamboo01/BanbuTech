#ifndef CAMERA_H
#define CAMERA_H

#include "Shader.h"
#include "FBO.h"
#include "glm.hpp"

class Camera
{
public:
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;
	Shader* PostProcessingShader;
	FrameBufferObject* FBO;

	unsigned viewWidth;
	unsigned viewHeight;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;

	Camera();
	~Camera();
	virtual void Init(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up, unsigned width, unsigned height);
	virtual void Reset();
	virtual void Update(double dt);
	void enableFrameBuffer();
	void disableFrameBuffer();
	void assignShader(const char* vertex_file_path, const char* fragment_file_path);
	void deleteShader();
};

#endif