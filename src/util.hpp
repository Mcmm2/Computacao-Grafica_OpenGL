#ifndef UTIL_HPP
#define UTIL_HPP

#include<string>
#include<GL/glew.h>

using namespace std;

string parseString(const char* path);
void compileError(GLuint shaderID);
void linkError(GLuint programID);
void compileVertex(GLuint* vertexShaderID, const char* code);
void compileFragment(GLuint* fragmentShaderID, const char* code);
GLuint parseShaders(const char* vertexPath, const char* fragmentPath);
void generateRandom(GLfloat color[], int size);

#endif