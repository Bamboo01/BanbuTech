#include "FBO.h"
#include <iostream>

FrameBufferObject::FrameBufferObject()
{
	//Allocate memory for frame buffer object and texture
	glGenFramebuffers(1, &FBO);
	glGenRenderbuffers(1, &RBO);
	glGenTextures(1, &frame_RGBA);
	glGenTextures(1, &frame_Depth);
}

FrameBufferObject::~FrameBufferObject()
{
	glDeleteFramebuffers(1, &FBO);
	glDeleteRenderbuffers(1, &RBO);
	glDeleteTextures(1, &frame_RGBA);
	glDeleteTextures(1, &frame_Depth);
}

bool FrameBufferObject::Init(unsigned width, unsigned height)
{
	m_width = width;
	m_height = height;

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	glBindTexture(GL_TEXTURE_2D, frame_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0); //increase 1024 if needed
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frame_RGBA, 0);

	glBindTexture(GL_TEXTURE_2D, frame_Depth);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0); //increase 1024 if needed
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, frame_Depth, 0);

	unsigned attachments[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, attachments);

	// Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Framebuffer error" << std::endl;
		return false;
	}

	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	return true;
}

void FrameBufferObject::BindForWriting()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glViewport(0, 0, m_width, m_height);
}

void FrameBufferObject::BindForReading(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, frame_RGBA);
}