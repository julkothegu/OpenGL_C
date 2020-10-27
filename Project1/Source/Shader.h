#pragma once
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "Camera.h"
#include <vector>
#include "DataDefs.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Shader
{
public: 
	unsigned int ID;

	void setUpShader(const char* vertexPath, const char* fragmentPath);
	void setUpGShader(const char* vertexPath, const char* fragmentPath, const char* geomPath);

	void use() const;
	void unbind() const;

	void setBool(const std::string& name, bool value) const;

	void setInt(const std::string& name, int value) const;

	void setFloat(const std::string& name, float value) const;

	void setVec2(const std::string& name, const glm::vec2& value) const;
	void setVec2(const std::string& name, float x, float y) const;

	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;

	void setVec4(const std::string& name, const glm::vec4& value) const;
	void setVec4(const std::string& name, float x, float y, float z, float w);

	void setMat2(const std::string& name, const glm::mat2& mat) const;

	void setMat3(const std::string& name, const glm::mat3& mat) const;

	void setMat4(const std::string& name, const glm::mat4& mat) const;

	void setUniform1i(const std::string& name, int value);
	void setUniform1f(const std::string& name, float value);
	void setUniform2f(const std::string& name, const glm::vec2& value);
	void setUniform3f(const std::string& name, const glm::vec3& value);
	void setUniform4f(const std::string& name, const glm::vec4& value);
	void setUniformMat2(const std::string& name, const glm::mat2& matrix);
	void setUniformMat3(const std::string& name, const glm::mat3& matrix);
	void setUniformMat4(const std::string& name, const glm::mat4& matrix);

	unsigned int getProgramID();
	unsigned int getVertex();
	unsigned int getFragment();
	unsigned int getGeom();

	glm::mat4 setUpPerspective(Shader shader, float fov, const unsigned int scr_width, const unsigned int scr_height, Camera camera);
	void setUpLight(Shader shader, float shininess, std::vector<glm::vec3> lightVecs, Camera camera);
	void setUpLightPoint(Shader shader, float shininess, std::vector<glm::vec3> lightVecs, Camera camera, LightInfo point);

private:
	unsigned int Vertex, Fragment, Geom;
	mutable std::unordered_map<std::string, GLint> UlocationCache;
	// utility function for checking shader compilation/linking errors.
	void checkCompileErrors(unsigned int shader, std::string type);

	GLint GetUniformLocation(const std::string& name) const;
};
