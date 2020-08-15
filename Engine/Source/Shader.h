#include <GL\glew.h>
#include <Mtx44.h>
#include <string>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <glm.hpp>
#include "Material.h"

#ifndef SHADER_HPP
#define SHADER_HPP

enum PROCESS_TYPE
{
	PRE_PROCESS,
	NORMAL_PROCESS,
	POST_PROCESS,
};

class Shader
{
protected:
	unsigned ID;
    GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {

		// Create the shaders
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		// Read the Vertex Shader code from the file
		std::string VertexShaderCode;
		std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
		if (VertexShaderStream.is_open()) {
			std::string Line = "";
			while (getline(VertexShaderStream, Line))
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();
		}
		else {
			printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
			getchar();
			return 0;
		}

		// Read the Fragment Shader code from the file
		std::string FragmentShaderCode;
		std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
		if (FragmentShaderStream.is_open()) {
			std::string Line = "";
			while (getline(FragmentShaderStream, Line))
				FragmentShaderCode += "\n" + Line;
			FragmentShaderStream.close();
		}



		GLint Result = GL_FALSE;
		int InfoLogLength;



		// Compile Vertex Shader
		printf("Compiling shader : %s\n", vertex_file_path);
		char const* VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);

		// Check Vertex Shader
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
			printf("%s\n", &VertexShaderErrorMessage[0]);
		}



		// Compile Fragment Shader
		printf("Compiling shader : %s\n", fragment_file_path);
		char const* FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(FragmentShaderID);

		// Check Fragment Shader
		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
			printf("%s\n", &FragmentShaderErrorMessage[0]);
		}



		// Link the program
		printf("Linking program\n");
		GLuint ProgramID = glCreateProgram();
		glAttachShader(ProgramID, VertexShaderID);
		glAttachShader(ProgramID, FragmentShaderID);
		glLinkProgram(ProgramID);

		// Check the program
		glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
			printf("%s\n", &ProgramErrorMessage[0]);
		}

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		ID = ProgramID;

		return ProgramID;
	}
	PROCESS_TYPE processtype;

	enum MATERIAL_UNIFORMS
	{
		U_MATERIAL_COLOR,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,

		U_COLOR_TEXTURE0,
		U_COLOR_TEXTURE1,
		U_COLOR_TEXTURE2,
		U_COLOR_TEXTURE3,
		U_COLOR_TEXTURE4,
		U_COLOR_TEXTURE5,
		U_COLOR_TEXTURE6,
		U_COLOR_TEXTURE7,
		U_COLOR_TEXTURE_NUM,

		U_MATERIAL_SPECULAR_MAP,
		U_MATERIAL_SPECULAR_MAP_ENABLED,

		U_NUM_LIGHTS,
		TOTAL_UNIFORMS
	};

	unsigned MaterialUniforms[TOTAL_UNIFORMS];

public:
	Shader(const char* vertex_file_path, const char* fragment_file_path, PROCESS_TYPE type = NORMAL_PROCESS)
		: processtype(NORMAL_PROCESS)
	{ 
		LoadShaders(vertex_file_path, fragment_file_path); 
	}

	~Shader() { glDeleteProgram(ID); }

	//Essential, reminder to run these in your children shaders >:(
	virtual void InitShader()
	{
		MaterialUniforms[U_MATERIAL_COLOR] = GetUniformLocation("material.kColor");
		MaterialUniforms[U_MATERIAL_AMBIENT] = GetUniformLocation("material.kAmbient");
		MaterialUniforms[U_MATERIAL_DIFFUSE] = GetUniformLocation("material.kDiffuse");
		MaterialUniforms[U_MATERIAL_SPECULAR] = GetUniformLocation("material.kSpecular");
		MaterialUniforms[U_MATERIAL_SHININESS] = GetUniformLocation("material.kShininess");

		MaterialUniforms[U_COLOR_TEXTURE0] = GetUniformLocation("material.colorTexture[0]");
		MaterialUniforms[U_COLOR_TEXTURE1] = GetUniformLocation("material.colorTexture[1]");
		MaterialUniforms[U_COLOR_TEXTURE2] = GetUniformLocation("material.colorTexture[2]");
		MaterialUniforms[U_COLOR_TEXTURE3] = GetUniformLocation("material.colorTexture[3]");
		MaterialUniforms[U_COLOR_TEXTURE4] = GetUniformLocation("material.colorTexture[4]");
		MaterialUniforms[U_COLOR_TEXTURE5] = GetUniformLocation("material.colorTexture[5]");
		MaterialUniforms[U_COLOR_TEXTURE6] = GetUniformLocation("material.colorTexture[6]");
		MaterialUniforms[U_COLOR_TEXTURE7] = GetUniformLocation("material.colorTexture[7]");
		MaterialUniforms[U_COLOR_TEXTURE_NUM] = GetUniformLocation("material.colorTextureNum");

		MaterialUniforms[U_MATERIAL_SPECULAR_MAP] = GetUniformLocation("material.SpecularMap");
		MaterialUniforms[U_MATERIAL_SPECULAR_MAP_ENABLED] = GetUniformLocation("material.SpecularMapEnabled");
	}

	virtual void UpdateShader(Material material)
	{
		setVec3(MaterialUniforms[U_MATERIAL_COLOR], material.kColor);
		setVec3(MaterialUniforms[U_MATERIAL_AMBIENT], material.kAmbient);
		setVec3(MaterialUniforms[U_MATERIAL_DIFFUSE], material.kDiffuse);
		setVec3(MaterialUniforms[U_MATERIAL_SPECULAR], material.kSpecular);
		setFloat(MaterialUniforms[U_MATERIAL_SHININESS], material.kShininess);

		for (int i = 0; i < material.numTexture; i++)
		{
			setInt(MaterialUniforms[U_COLOR_TEXTURE0 + i], material.colorTexture[i]);
		}
		setInt(MaterialUniforms[U_COLOR_TEXTURE_NUM], material.numTexture);

		setInt(MaterialUniforms[U_MATERIAL_SPECULAR_MAP], material.specularMap);
		setInt(MaterialUniforms[U_MATERIAL_SPECULAR_MAP_ENABLED], material.specularMapEnabled);
	}

    unsigned GetUniformLocation(std::string name)
    {
        return glGetUniformLocation(ID, name.c_str());
    }

    void UseShader()
    {
        glUseProgram(ID);
    }


	//Utility uniform functions
	void setBool(unsigned location, bool value) const
	{
		glUniform1i(location, (int)value);
	}

	void setInt(unsigned location, int value) const
	{
		glUniform1i(location, value);
	}

	void setFloat(unsigned location, float value) const
	{
		glUniform1f(location, value);
	}

	void setVec2(unsigned location, const glm::vec2& value) const
	{
		glUniform2fv(location, 1, &value[0]);
	}

	void setVec2(unsigned location, float x, float y) const
	{
		glUniform2f(location, x, y);
	}

	void setVec3(unsigned location, const glm::vec3& value) const
	{
		glUniform3fv(location, 1, &value[0]);
	}

	void setVec3(unsigned location, float x, float y, float z) const
	{
		glUniform3f(location, x, y, z);
	}

	void setVec4(unsigned location, const glm::vec4& value) const
	{
		glUniform4fv(location, 1, &value[0]);
	}

	void setVec4(unsigned location, float x, float y, float z, float w)
	{
		glUniform4f(location, x, y, z, w);
	}

	void setMat2(unsigned location, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(location, 1, GL_FALSE, &mat[0][0]);
	}

	void setMat3(unsigned location, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(location, 1, GL_FALSE, &mat[0][0]);
	}

	void setMat4(unsigned location, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
	}

	const PROCESS_TYPE &proccess_type = processtype;

	operator unsigned() const { return ID; }
};
#endif
