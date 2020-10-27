#include "precomp.h"
#include "Shader.h"

void Shader::setUpShader(const char* vertexPath, const char* fragmentPath)
{
	std::fstream pVertex(vertexPath);
	std::fstream pFragment(fragmentPath);

	std::string vCode;
	std::string fCode;

	std::string p;
	std::string f;

	if (pVertex && pFragment) {
		std::stringstream p;
		std::stringstream f;

		p << pVertex.rdbuf();
		f << pFragment.rdbuf();

		vCode = p.str();
		fCode = f.str();
	}

	const char* vShaderCode = vCode.c_str();
	const char* fShaderCode = fCode.c_str();

	Vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(Vertex, 1, &vShaderCode, NULL);
	glCompileShader(Vertex);
	checkCompileErrors(Vertex, "vertex");

	Fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(Fragment, 1, &fShaderCode, NULL);
	glCompileShader(Fragment);
	checkCompileErrors(Fragment, "fragment");

	ID = glCreateProgram();
	glAttachShader(ID, Vertex);
	glAttachShader(ID, Fragment);
	glLinkProgram(ID);

	/*std::cout << vShaderCode << std::endl;
	std::cout << fShaderCode << std::endl;*/

	glDeleteShader(Vertex);
	glDeleteShader(Fragment);
}

void Shader::setUpGShader(const char* vertexPath, const char* fragmentPath, const char* geomPath)
{
	std::fstream pVertex(vertexPath);
	std::fstream pFragment(fragmentPath);
	std::fstream gFragment(geomPath);

	std::string vCode;
	std::string fCode;
	std::string gCode;

	std::string p;
	std::string f;
	std::string g;

	if (pVertex && pFragment && gFragment) {
		std::stringstream p;
		std::stringstream f;
		std::stringstream g;

		p << pVertex.rdbuf();
		f << pFragment.rdbuf();
		g << gFragment.rdbuf();

		vCode = p.str();
		fCode = f.str();
		gCode = g.str();
	}

	const char* vShaderCode = vCode.c_str();
	const char* fShaderCode = fCode.c_str();
	const char* gShaderCode = gCode.c_str();

	Vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(Vertex, 1, &vShaderCode, NULL);
	glCompileShader(Vertex);
	checkCompileErrors(Vertex, "vertex");

	Fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(Fragment, 1, &fShaderCode, NULL);
	glCompileShader(Fragment);
	checkCompileErrors(Fragment, "fragment");

	Geom = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(Geom, 1, &gShaderCode, NULL);
	glCompileShader(Geom);
	checkCompileErrors(Geom, "geometry");

	ID = glCreateProgram();
	glAttachShader(ID, Vertex);
	glAttachShader(ID, Fragment);
	glAttachShader(ID, Geom);
	glLinkProgram(ID);

	/*std::cout << vShaderCode << std::endl;
	std::cout << fShaderCode << std::endl;*/

	glDeleteShader(Vertex);
	glDeleteShader(Fragment);
	glDeleteShader(Geom);
	
}

void Shader::use() const
{
	glUseProgram(ID);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

unsigned int Shader::getProgramID()
{
	return ID;
}

unsigned int Shader::getVertex()
{
	return Vertex;
}

unsigned int Shader::getFragment()
{
	return Fragment;
}

unsigned int Shader::getGeom()
{
	return Geom;
}

glm::mat4 Shader::setUpPerspective(Shader shader, float fov, const unsigned int scr_width, const unsigned int scr_height, Camera camera)
{
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(fov), (float)scr_width / (float)scr_height, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();

	shader.setUniformMat4("projection", projection);
	shader.setUniformMat4("view", view);
	shader.setUniformMat4("model", model);

	return model;
}

void Shader::setUpLightPoint(Shader shader, float shininess, std::vector<glm::vec3> lightVecs, Camera camera, LightInfo point)
{
	shader.setUniform3f("viewPos", camera.cameraPos);
	shader.setFloat("material.shininess", shininess);

	shader.setUniform3f("pointLight.ambient", lightVecs[0]);
	shader.setUniform3f("pointLight.diffuse", lightVecs[1]);
	shader.setUniform3f("pointLight.specular", lightVecs[2]);
	shader.setUniform3f("pointLight.direction", lightVecs[3]);

	shader.setFloat("pointLight.constant", point.constant);
	shader.setFloat("pointLight.linear", point.linear);
	shader.setFloat("pointLight.quadratic", point.quadratic);
}

void Shader::setUpLight(Shader shader, float shininess, std::vector<glm::vec3> lightVecs, Camera camera)
{
	shader.setUniform3f("viewPos", camera.cameraPos);
	shader.setFloat("material.shininess", shininess);

	shader.setUniform3f("DirLights.ambient", lightVecs[0]);
	shader.setUniform3f("DirLights.diffuse", lightVecs[1]);
	shader.setUniform3f("DirLights.specular", lightVecs[2]);
	shader.setUniform3f("DirLights.direction", lightVecs[3]);
}


void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setUniform1i(const std::string& name, int value)
{
	GLint location = GetUniformLocation(name);
	glUniform1i(location, value);
}

void Shader::setUniform1f(const std::string& name, float value)
{
	GLint location = GetUniformLocation(name);
	glUniform1i(location, value);
}

void Shader::setUniform2f(const std::string& name, const glm::vec2& value)
{
	GLint location = GetUniformLocation(name);
	glUniform2f(location, value.x, value.y);
}

void Shader::setUniform3f(const std::string& name, const glm::vec3& value)
{
	GLint location = GetUniformLocation(name);
	glUniform3f(location, value.x, value.y, value.z);
}

void Shader::setUniform4f(const std::string& name, const glm::vec4& value)
{
	GLint location = GetUniformLocation(name);
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::setUniformMat2(const std::string& name, const glm::mat2& matrix)
{
	GLint location = GetUniformLocation(name);
	glUniformMatrix2fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setUniformMat3(const std::string& name, const glm::mat3& matrix)
{
	GLint location = GetUniformLocation(name);
	glUniformMatrix3fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	GLint location = GetUniformLocation(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

GLint Shader::GetUniformLocation(const std::string& name) const
{
	if (UlocationCache.find(name) != UlocationCache.end())
		return UlocationCache[name];
	
	GLint location = glGetUniformLocation(ID, name.c_str());
	UlocationCache[name] = location;
	return location;
}
