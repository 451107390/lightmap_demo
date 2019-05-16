#include "program.h"

Program::Program(){
	for (int i = 0; i < ENumShader; ++i){
		source[i] = "";
	}
}

void Program::Init(){
	id = glCreateProgram();
	GLuint vertex = CreateShader(GL_VERTEX_SHADER, source[EVertexShader]);
	GLuint geo;
	bool hasGeo = source[EGeoShader] != "" ? true : false;
	if (hasGeo)
		geo = CreateShader(GL_GEOMETRY_SHADER, source[EGeoShader]);
	GLuint frag = CreateShader(GL_FRAGMENT_SHADER, source[EFragShader]);

	GLint success;
	char infoLog[512];
	glAttachShader(id, vertex);
	if (hasGeo)
		glAttachShader(id, geo);
	glAttachShader(id, frag);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success){
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		fprintf(stderr, "Shader Program Linking Failed, [%s]\n", infoLog);
	}

	glDeleteShader(vertex);
	if (hasGeo)
		glDeleteShader(geo);
	glDeleteShader(frag);
}

GLuint Program::CreateShader(GLuint id, string code){
	const char* shaderCode = code.c_str();
	GLuint shader;
	GLint success;
	char infoLog[512];

	shader = glCreateShader(id);
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success){
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		fprintf(stderr, "%s Compilation Failed, [%s]\n", id == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader", infoLog);
	}

	return shader;
}

void Program::SetSource(int id, string str){
	source[id] = str;
}

void Program::Bind() const{
	glUseProgram(id);
}

void Program::UnBind() const{
	glUseProgram(0);
}

void Program::SetBool(const string& name, bool value) const{
	GLint location = glGetUniformLocation(id, name.c_str());
	glUniform1i(location, (int)value);
}

void Program::SetInt(const string& name, int value) const{
	GLint location = glGetUniformLocation(id, name.c_str());
	glUniform1i(location, value);
}

void Program::SetFloat(const string& name, float value) const{
	GLint location = glGetUniformLocation(id, name.c_str());
	glUniform1f(location, value);
}

void Program::SetVec2(const string& name, vec2& value) const{
	GLint location = glGetUniformLocation(id, name.c_str());
	glUniform2fv(location, 1, &value[0]);
}

void Program::SetVec2(const string& name, float x, float y) const{
	GLint location = glGetUniformLocation(id, name.c_str());
	glUniform2f(location, x, y);
}

void Program::SetVec3(const string& name, vec3& value) const{
	GLint location = glGetUniformLocation(id, name.c_str());
	glUniform3fv(location, 1, &value[0]);
}

void Program::SetVec3(const string& name, float x, float y, float z) const{
	GLint location = glGetUniformLocation(id, name.c_str());
	glUniform3f(location, x, y, z);
}

void Program::SetVec4(const string& name, vec4& value) const{
	GLint location = glGetUniformLocation(id, name.c_str());
	glUniform4fv(location, 1, &value[0]);
}

void Program::SetVec4(const string& name, float x, float y, float z, float w) const{
	GLint location = glGetUniformLocation(id, name.c_str());
	glUniform4f(location, x, y, z, w);
}

void Program::SetMat4(const string& name, mat4& value) const{
	GLint location = glGetUniformLocation(id, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

void Program::SetMat4(const string& name, float value[16]) const{
	GLint location = glGetUniformLocation(id, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, value);
}