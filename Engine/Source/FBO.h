#ifndef FBO_H
#define FBO_H

#include <GL/glew.h>

class FrameBufferObject
{
public:
    FrameBufferObject();
    ~FrameBufferObject();

    virtual bool Init(unsigned width, unsigned height);
    virtual void BindForWriting();
    virtual void BindForReading(GLenum textureUnit);

    GLuint GetFBO() { return FBO; }
    GLuint GetFrame() { return frame_RGBA; }
    GLuint GetDepth() { return frame_Depth; }
    unsigned GetWidth() { return m_width; }
    unsigned GetHeight() { return m_height; }

private:
    unsigned FBO;		
    unsigned RBO;
    unsigned frame_RGBA;	
    unsigned frame_Depth;
    unsigned m_width;
    unsigned m_height;
};

#endif

