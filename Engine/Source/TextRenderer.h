//#pragma once
//
//#include "shader.h"
//#include <glm.hpp>
//#include <map>
//#include "Mesh.h"
//
//class CTextRenderer : public Mesh
//{
//	// Holds all state information relevant to a character as loaded using FreeType
//	struct Character {
//		GLuint TextureID;   // ID handle of the glyph texture
//		glm::ivec2 Size;    // Size of glyph
//		glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
//		GLuint Advance;    // Horizontal offset to advance to next glyph
//	};
//
//public:
//	// Init
//	void Init();
//
//	// Update
//	void Update();
//
//	// PreRender
//	void PreRender();
//
//	// Render
//	void Render(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 colour);
//
//	// PostRender
//	void PostRender(void);
//
//	// Set a shader to this class instance
//	void SetShader(Shader* cShader);
//
//protected:
//	// Handler to the Shader Program instance
//	Shader* cShader;
//	unsigned int VBO, VAO, EBO;
//
//	// Map of characters
//	std::map<GLchar, Character> Characters;
//
//	// Constructor
//	CTextRenderer(void);
//
//	// Destructor
//	virtual ~CTextRenderer(void);
//};
//
