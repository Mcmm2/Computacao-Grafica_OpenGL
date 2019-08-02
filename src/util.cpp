#include<stdlib.h>
#include<stdio.h>
#include<sstream>
#include<fstream>
#include<vector>

#include"util.hpp"

string parseString(const char* path){
    ifstream in(path);
    if(in.is_open()){
        stringstream ss;
        ss << in.rdbuf();
        return ss.str();
    }
    else{
        printf("Impossible to open %s\n", path);
        getchar();
        exit(-1);
    }
}

void compileError(GLuint shaderID){
    GLint Result = GL_FALSE;
	int InfoLogLength;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> Message(InfoLogLength+1);
		glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &Message[0]);
		printf("..%s\n", &Message[0]);
	}
}

void linkError(GLuint programID){
    GLint Result = GL_FALSE;
	int InfoLogLength;
    glGetShaderiv(programID, GL_LINK_STATUS, &Result);
	glGetShaderiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    //printf("%d", InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> Message(InfoLogLength+1);
		glGetShaderInfoLog(programID, InfoLogLength, NULL, &Message[0]);
		//printf(".%s\n", &Message[0]);
	}
}

void compileVertex(GLuint* vertexShaderID, const char* code){
    //Creatint vertex shaders
    printf("Compiling Vertex Shader...\n");
    glShaderSource(*vertexShaderID, 1, &code, NULL);
    glCompileShader(*vertexShaderID);
    compileError(*vertexShaderID);
}

void compileFragment(GLuint* fragmentShaderID, const char* code){
    //Creating fragment shaders
    printf("Compiling Fragment Shader...\n");
    glShaderSource(*fragmentShaderID, 1, &code, NULL);
    glCompileShader(*fragmentShaderID);
    compileError(*fragmentShaderID);
}

GLuint parseShaders(const char* vertexPath, const char* fragmentPath){
    //Read vertex shader and compile
    string vertexShaderCode = parseString(vertexPath);
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    compileVertex(&vertexShaderID, vertexShaderCode.c_str());

    //Read fragment shader and compile
    string fragmentShaderCode = parseString(fragmentPath);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    compileFragment(&fragmentShaderID, fragmentShaderCode.c_str());

    //Linking Shaders
    printf("Linking program...\n");
    GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
    linkError(programID);

    glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}

void generateRandom(GLfloat color[], int size){
    for(int i = 0; i < size; i++)
        color[i] = (float)rand()/RAND_MAX;
}