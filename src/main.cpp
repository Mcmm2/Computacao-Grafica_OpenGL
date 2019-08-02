// Reference to the openGL function: http://docs.gl/ 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>


#include "../extern/glm-0.9.9.5/glm/glm.hpp"
#include "controls.hpp"
#include "util.hpp"

using namespace std;

#include<GL/glew.h>
#include<GLFW/glfw3.h>


#include "../extern/glm-0.9.9.5/glm/gtc/matrix_transform.hpp"

void print(GLfloat color[], int size){
    for(int i = 0; i < size; i++)
        printf("%f\n", color[i]);
}

//Global to facilitate the use of the camera library
GLFWwindow* window;

int main(){
    glewExperimental = true;
    if(!glfwInit()){
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    window = glfwCreateWindow(1024, 768, "OpenGL Window", NULL, NULL);

    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }


    printf("OpenGL version: %s\n", glGetString(GL_VERSION));

    glEnable(GL_CULL_FACE);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Faz com que o teclado funcione de maneira diferente do clique

    // Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);


    GLfloat triangle[] = {-1.0f,-1.0f,-1.0f, // triangle 1 : begin
                          -1.0f,-1.0f, 1.0f,
                          -1.0f, 1.0f, 1.0f, // triangle 1 : end
                          1.0f, 1.0f,-1.0f, // triangle 2 : begin
                          -1.0f,-1.0f,-1.0f,
                          -1.0f, 1.0f,-1.0f, // triangle 2 : end
                          1.0f,-1.0f, 1.0f,
                          -1.0f,-1.0f,-1.0f,
                          1.0f,-1.0f,-1.0f,
                          1.0f, 1.0f,-1.0f,
                          1.0f,-1.0f,-1.0f,
                          -1.0f,-1.0f,-1.0f,
                          -1.0f,-1.0f,-1.0f,
                          -1.0f, 1.0f, 1.0f,
                          -1.0f, 1.0f,-1.0f,
                          1.0f,-1.0f, 1.0f,
                          -1.0f,-1.0f, 1.0f,
                          -1.0f,-1.0f,-1.0f,
                          -1.0f, 1.0f, 1.0f,
                          -1.0f,-1.0f, 1.0f,
                          1.0f,-1.0f, 1.0f,
                          1.0f, 1.0f, 1.0f,
                          1.0f,-1.0f,-1.0f,
                          1.0f, 1.0f,-1.0f,
                          1.0f,-1.0f,-1.0f,
                          1.0f, 1.0f, 1.0f,
                          1.0f,-1.0f, 1.0f,
                          1.0f, 1.0f, 1.0f,
                          1.0f, 1.0f,-1.0f,
                          -1.0f, 1.0f,-1.0f,
                          1.0f, 1.0f, 1.0f,
                          -1.0f, 1.0f,-1.0f,
                          -1.0f, 1.0f, 1.0f,
                          1.0f, 1.0f, 1.0f,
                          -1.0f, 1.0f, 1.0f,
                          1.0f,-1.0f, 1.0f   };
    GLfloat colors[12*3*3];
    srand(time(0));
    generateRandom(colors, 12*3*3);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    //Triangle Data
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    //Color Data
    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint programID = parseShaders("../res/shaders/vertexShader.shader", "../res/shaders/fragmentShader.shader");


    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) 1024 / (float)768, 0.1f, 100.0f);
    
    // Or, for an ortho camera :
    //glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
    
 /*   
    // Camera matrix
    glm::mat4 View = glm::lookAt(
        glm::vec3(4,3,-3), // Camera is at (4,3,3), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
        );
    
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around
*/

    // Get a handle for our "MVP" uniform
    // Only during the initialisation
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    do{

       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programID);

        // Compute the MVP matrix from keyboard and mouse input
        computeMatricesFromInputs();
        glm::mat4 ProjectionMatrix = getProjectionMatrix();
        glm::mat4 ViewMatrix = getViewMatrix();
        glm::mat4 ModelMatrix = glm::mat4(1.0);
        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

        // Send our transformation to the currently bound shader, in the "MVP" uniform
        // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        //Triangle Rendering
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        //Colors Rendering
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 12*3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);

        glfwSwapBuffers(window); //Swap back buffer with front buffer(front buffer is what is on the screen and back buffer is what is on the back to be rendered)
        glfwPollEvents();

    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS and !glfwWindowShouldClose(window));

}
