#ifndef CAMERA_H
#define CAMERA_H

#include "Shader.h"
#include "FBO.h"
#include "glm.hpp"

enum CAMERA_TYPE
{
	CAMERA_MAIN,
	CAMERA_NORMAL,
	NUM_TYPES
};

enum CAMERA_MODE
{
	MODE_ORTHOGRAPHIC,
	MODE_PERSPECTIVE
};

class Camera
{
private:
	Shader* PostProcessingShader;
	std::vector<unsigned*> targetTexture;
	
public:

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 target;
	glm::vec3 up;
	glm::vec3 right;
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	int viewWidth;
	int viewHeight;
	CAMERA_TYPE type;
	CAMERA_MODE mode;
	FrameBufferObject* FBO;
	float FOV;

	Camera(
		const glm::vec3& pos,
		const glm::vec3& rotation,
		unsigned width, unsigned height,
		float FOV,
		CAMERA_TYPE type,
		CAMERA_MODE mode);
	Camera();
	~Camera();

	void Init();
	void assignPostProcessingShader(const char* vertex_file_path, const char* fragment_file_path);
	Shader* getPostProcessingShader();
	void deletePostProcessingShader();

	void UpdateAssignedTextures();
	void assignTargetTexture(unsigned* target);
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();
};

#endif