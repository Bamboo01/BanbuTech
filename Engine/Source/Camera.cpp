#include "Camera.h"

Camera::Camera()
{
	PostProcessingShader = nullptr;
}

Camera::~Camera()
{
	if (PostProcessingShader)
	{
		glDeleteProgram(*PostProcessingShader);
		delete PostProcessingShader;
	}
	if (FBO)
	{
		delete FBO;
	}
}

void Camera::Init(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up, unsigned width, unsigned height)
{
	this->position = pos;
	this->target = target;
	this->up = up;
	viewWidth = width;
	viewHeight = height;
}

void Camera::Reset()
{

}

void Camera::Update(double dt)
{

}

void Camera::enableFrameBuffer()
{
	if (FBO)
	{
		return;
	}
	FBO = new FrameBufferObject;
	FBO->Init(viewWidth, viewHeight);
}

void Camera::disableFrameBuffer()
{
	if (FBO)
	{
		delete FBO;
	}
}

void Camera::assignShader(const char* vertex_file_path, const char* fragment_file_path)
{
	if (PostProcessingShader)
	{
		return;
	}
	PostProcessingShader = new Shader(vertex_file_path, fragment_file_path);
}

void Camera::deleteShader()
{
	if (PostProcessingShader)
	{
		delete PostProcessingShader;
	}
}
