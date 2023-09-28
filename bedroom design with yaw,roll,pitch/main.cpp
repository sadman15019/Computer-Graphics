//
//  main.cpp
//  3D Object Drawing
//
//  Created by Nazirul Hasan on 4/9/23.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// modelling transform
float rotateAngle_X = 45.0;
float rotateAngle_Y = 45.0;
float rotateAngle_Z = 45.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;


bool fan_on = false;

// camera
Camera camera(glm::vec3(-3.0f, 3.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    /*float cube_vertices[] = {
        0.0f, 0.0f, 0.0f, 0.3f, 0.8f, 0.5f,
        0.5f, 0.0f, 0.0f, 0.5f, 0.4f, 0.3f,
        0.5f, 0.5f, 0.0f, 0.2f, 0.7f, 0.3f,
        0.0f, 0.5f, 0.0f, 0.6f, 0.2f, 0.8f,
        0.0f, 0.0f, 0.5f, 0.8f, 0.3f, 0.6f,
        0.5f, 0.0f, 0.5f, 0.4f, 0.4f, 0.8f,
        0.5f, 0.5f, 0.5f, 0.2f, 0.3f, 0.6f,
        0.0f, 0.5f, 0.5f, 0.7f, 0.5f, 0.4f
    };*/
    /*float cube_vertices[] = {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.5f,
        0.5f, 0.0f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.0f, 0.5f, 0.5f
    };*/
    float cube_vertices1[] = {

        //A
        0.0f, 0.0f, 0.0f, 0.8392f, 0.6196f, 0.2f,
        0.5f, 0.0f, 0.0f, 0.8392f, 0.6196f, 0.2f,
        0.5f, 0.5f, 0.0f, 0.8392f, 0.6196f, 0.2f,
        0.0f, 0.5f, 0.0f, 0.8392f, 0.6196f, 0.2f,

        //B

        0.5f, 0.0f, 0.0f, 0.8392f, 0.6196f, 0.2f,
        0.5f, 0.5f, 0.0f, 0.8392f, 0.6196f, 0.2f,
        0.5f, 0.0f, 0.5f, 0.8392f, 0.6196f, 0.2f,
        0.5f, 0.5f, 0.5f, 0.8392f, 0.6196f, 0.2f,

        //C

        0.0f, 0.0f, 0.5f, 0.8392f, 0.6196f, 0.2f,
        0.5f, 0.0f, 0.5f, 0.8392f, 0.6196f, 0.2f,
        0.5f, 0.5f, 0.5f, 0.8392f, 0.6196f, 0.2f,
        0.0f, 0.5f, 0.5f, 0.8392f, 0.6196f, 0.2f,

        //D

        0.0f, 0.0f, 0.5f, 0.8392f, 0.6196f, 0.2f,
        0.0f, 0.5f, 0.5f, 0.8392f, 0.6196f, 0.2f,
        0.0f, 0.5f, 0.0f, 0.8392f, 0.6196f, 0.2f,
        0.0f, 0.0f, 0.0f, 0.8392f, 0.6196f, 0.2f,

        //E

        0.5f, 0.5f, 0.5f, 0.8392f, 0.6196f, 0.2f,
        0.5f, 0.5f, 0.0f, 0.8392f, 0.6196f, 0.2f,
        0.0f, 0.5f, 0.0f, 0.8392f, 0.6196f, 0.2f,
        0.0f, 0.5f, 0.5f, 0.8392f, 0.6196f, 0.2f,

        //F

        0.0f, 0.0f, 0.0f, 0.8392f, 0.6196f, 0.2f,
        0.5f, 0.0f, 0.0f, 0.8392f, 0.6196f, 0.2f,
        0.5f, 0.0f, 0.5f, 0.8392f, 0.6196f, 0.2f,
        0.0f, 0.0f, 0.5f, 0.8392f, 0.6196f, 0.2f


    };

    float cube_vertices2[] = {

        //A
        0.0f, 0.0f, 0.0f, 0.9058f, 0.8862f, 0.8235f,
        0.5f, 0.0f, 0.0f, 0.9058f, 0.8862f, 0.8235f,
        0.5f, 0.5f, 0.0f, 0.9058f, 0.8862f, 0.8235f,
        0.0f, 0.5f, 0.0f, 0.9058f, 0.8862f, 0.8235f,

        //B

        0.5f, 0.0f, 0.0f, 0.9058f, 0.8862f, 0.8235f,
        0.5f, 0.5f, 0.0f, 0.9058f, 0.8862f, 0.8235f,
        0.5f, 0.0f, 0.5f, 0.9058f, 0.8862f, 0.8235f,
        0.5f, 0.5f, 0.5f, 0.9058f, 0.8862f, 0.8235f,

        //C

        0.0f, 0.0f, 0.5f, 0.9058f, 0.8862f, 0.8235f,
        0.5f, 0.0f, 0.5f, 0.9058f, 0.8862f, 0.8235f,
        0.5f, 0.5f, 0.5f, 0.9058f, 0.8862f, 0.8235f,
        0.0f, 0.5f, 0.5f, 0.9058f, 0.8862f, 0.8235f,

        //D

        0.0f, 0.0f, 0.5f, 0.9058f, 0.8862f, 0.8235f,
        0.0f, 0.5f, 0.5f, 0.9058f, 0.8862f, 0.8235f,
        0.0f, 0.5f, 0.0f, 0.9058f, 0.8862f, 0.8235f,
        0.0f, 0.0f, 0.0f, 0.9058f, 0.8862f, 0.8235f,

        //E

        0.5f, 0.5f, 0.5f, 0.9058f, 0.8862f, 0.8235f,
        0.5f, 0.5f, 0.0f, 0.9058f, 0.8862f, 0.8235f,
        0.0f, 0.5f, 0.0f, 0.9058f, 0.8862f, 0.8235f,
        0.0f, 0.5f, 0.5f, 0.9058f, 0.8862f, 0.8235f,

        //F

        0.0f, 0.0f, 0.0f, 0.9058f, 0.8862f, 0.8235f,
        0.5f, 0.0f, 0.0f, 0.9058f, 0.8862f, 0.8235f,
        0.5f, 0.0f, 0.5f,0.9058f, 0.8862f, 0.8235f,
        0.0f, 0.0f, 0.5f, 0.9058f, 0.8862f, 0.8235f


    };

    float cube_vertices3[] = {

        //A
        0.0f, 0.0f, 0.0f, 0.3137f, 0.03529f, 0.0784f,
        0.5f, 0.0f, 0.0f, 0.3137f, 0.03529f, 0.0784f,
        0.5f, 0.5f, 0.0f, 0.3137f, 0.03529f, 0.0784f,
        0.0f, 0.5f, 0.0f, 0.3137f, 0.03529f, 0.0784f,

        //B

        0.5f, 0.0f, 0.0f, 0.3137f, 0.03529f, 0.0784f,
        0.5f, 0.5f, 0.0f, 0.3137f, 0.03529f, 0.0784f,
        0.5f, 0.0f, 0.5f,0.3137f, 0.03529f, 0.0784f,
        0.5f, 0.5f, 0.5f, 0.3137f, 0.03529f, 0.0784f,

        //C

        0.0f, 0.0f, 0.5f, 0.3137f, 0.03529f, 0.0784f,
        0.5f, 0.0f, 0.5f, 0.3137f, 0.03529f, 0.0784f,
        0.5f, 0.5f, 0.5f, 0.3137f, 0.03529f, 0.0784f,
        0.0f, 0.5f, 0.5f, 0.3137f, 0.03529f, 0.0784f,

        //D

        0.0f, 0.0f, 0.5f, 0.3137f, 0.03529f, 0.0784f,
        0.0f, 0.5f, 0.5f, 0.3137f, 0.03529f, 0.0784f,
        0.0f, 0.5f, 0.0f, 0.3137f, 0.03529f, 0.0784f,
        0.0f, 0.0f, 0.0f, 0.3137f, 0.03529f, 0.0784f,

        //E

        0.5f, 0.5f, 0.5f, 0.3137f, 0.03529f, 0.0784f,
        0.5f, 0.5f, 0.0f, 0.3137f, 0.03529f, 0.0784f,
        0.0f, 0.5f, 0.0f, 0.3137f, 0.03529f, 0.0784f,
        0.0f, 0.5f, 0.5f, 0.3137f, 0.03529f, 0.0784f,

        //F

        0.0f, 0.0f, 0.0f, 0.3137f, 0.03529f, 0.0784f,
        0.5f, 0.0f, 0.0f, 0.3137f, 0.03529f, 0.0784f,
        0.5f, 0.0f, 0.5f,0.3137f, 0.03529f, 0.0784f,
        0.0f, 0.0f, 0.5f, 0.3137f, 0.03529f, 0.0784f,


    };

    float cube_vertices4[] = {

        //A
        0.0f, 0.0f, 0.0f, 0.9019f, 0.6039f, 0.2941f,
        0.5f, 0.0f, 0.0f,  0.9019f, 0.6039f, 0.2941f,
        0.5f, 0.5f, 0.0f,  0.9019f, 0.6039f, 0.2941f,
        0.0f, 0.5f, 0.0f,  0.9019f, 0.6039f, 0.2941f,

        //B

        0.5f, 0.0f, 0.0f,  0.9019f, 0.6039f, 0.2941f,
        0.5f, 0.5f, 0.0f,  0.9019f, 0.6039f, 0.2941f,
        0.5f, 0.0f, 0.5f, 0.9019f, 0.6039f, 0.2941f,
        0.5f, 0.5f, 0.5f,  0.9019f, 0.6039f, 0.2941f,

        //C

        0.0f, 0.0f, 0.5f,  0.9019f, 0.6039f, 0.2941f,
        0.5f, 0.0f, 0.5f,  0.9019f, 0.6039f, 0.2941f,
        0.5f, 0.5f, 0.5f,  0.9019f, 0.6039f, 0.2941f,
        0.0f, 0.5f, 0.5f,  0.9019f, 0.6039f, 0.2941f,

        //D

        0.0f, 0.0f, 0.5f,  0.9019f, 0.6039f, 0.2941f,
        0.0f, 0.5f, 0.5f,  0.9019f, 0.6039f, 0.2941f,
        0.0f, 0.5f, 0.0f,  0.9019f, 0.6039f, 0.2941f,
        0.0f, 0.0f, 0.0f,  0.9019f, 0.6039f, 0.2941f,

        //E

        0.5f, 0.5f, 0.5f,  0.9019f, 0.6039f, 0.2941f,
        0.5f, 0.5f, 0.0f,  0.9019f, 0.6039f, 0.2941f,
        0.0f, 0.5f, 0.0f,  0.9019f, 0.6039f, 0.2941f,
        0.0f, 0.5f, 0.5f,  0.9019f, 0.6039f, 0.2941f,

        //F

        0.0f, 0.0f, 0.0f,  0.9019f, 0.6039f, 0.2941f,
        0.5f, 0.0f, 0.0f,  0.9019f, 0.6039f, 0.2941f,
        0.5f, 0.0f, 0.5f, 0.9019f, 0.6039f, 0.2941f,
        0.0f, 0.0f, 0.5f,  0.9019f, 0.6039f, 0.2941f,


    };

    float cube_vertices5[] = {

        //A
        0.0f, 0.0f, 0.0f, 0.7098f, 0.3960f, 0.1137f,
        0.5f, 0.0f, 0.0f,  0.7098f, 0.3960f, 0.1137f,
        0.5f, 0.5f, 0.0f,  0.7098f, 0.3960f, 0.1137f,
        0.0f, 0.5f, 0.0f, 0.7098f, 0.3960f, 0.1137f,

        //B

        0.5f, 0.0f, 0.0f,  0.7098f, 0.3960f, 0.1137f,
        0.5f, 0.5f, 0.0f, 0.7098f, 0.3960f, 0.1137f,
        0.5f, 0.0f, 0.5f,0.7098f, 0.3960f, 0.1137f,
        0.5f, 0.5f, 0.5f,0.7098f, 0.3960f, 0.1137f,

        //C

        0.0f, 0.0f, 0.5f, 0.7098f, 0.3960f, 0.1137f,
        0.5f, 0.0f, 0.5f, 0.7098f, 0.3960f, 0.1137f,
        0.5f, 0.5f, 0.5f, 0.7098f, 0.3960f, 0.1137f,
        0.0f, 0.5f, 0.5f,  0.7098f, 0.3960f, 0.1137f,

        //D

        0.0f, 0.0f, 0.5f,  0.7098f, 0.3960f, 0.1137f,
        0.0f, 0.5f, 0.5f,  0.7098f, 0.3960f, 0.1137f,
        0.0f, 0.5f, 0.0f, 0.7098f, 0.3960f, 0.1137f,
        0.0f, 0.0f, 0.0f, 0.7098f, 0.3960f, 0.1137f,

        //E

        0.5f, 0.5f, 0.5f,  0.7098f, 0.3960f, 0.1137f,
        0.5f, 0.5f, 0.0f,  0.7098f, 0.3960f, 0.1137f,
        0.0f, 0.5f, 0.0f,  0.7098f, 0.3960f, 0.1137f,
        0.0f, 0.5f, 0.5f,  0.7098f, 0.3960f, 0.1137f,

        //F

        0.0f, 0.0f, 0.0f,  0.7098f, 0.3960f, 0.1137f,
        0.5f, 0.0f, 0.0f,  0.7098f, 0.3960f, 0.1137f,
        0.5f, 0.0f, 0.5f,0.7098f, 0.3960f, 0.1137f,
        0.0f, 0.0f, 0.5f,  0.7098f, 0.3960f, 0.1137f,


    };
    
    float cube_vertices6[] = {

        //A
        0.0f, 0.0f, 0.0f, 0.2549f, 0.0980f, 0.0f,
        0.5f, 0.0f, 0.0f, 0.2549f, 0.0980f, 0.0f,
        0.5f, 0.5f, 0.0f,  0.2549f, 0.0980f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.2549f, 0.0980f, 0.0f,

        //B

        0.5f, 0.0f, 0.0f,  0.2549f, 0.0980f, 0.0f,
        0.5f, 0.5f, 0.0f, 0.2549f, 0.0980f, 0.0f,
        0.5f, 0.0f, 0.5f,0.2549f, 0.0980f, 0.0f,
        0.5f, 0.5f, 0.5f,0.2549f, 0.0980f, 0.0f,

        //C

        0.0f, 0.0f, 0.5f, 0.2549f, 0.0980f, 0.0f,
        0.5f, 0.0f, 0.5f, 0.2549f, 0.0980f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.2549f, 0.0980f, 0.0f,
        0.0f, 0.5f, 0.5f,  0.2549f, 0.0980f, 0.0f,

        //D

        0.0f, 0.0f, 0.5f,  0.2549f, 0.0980f, 0.0f,
        0.0f, 0.5f, 0.5f,  0.2549f, 0.0980f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.2549f, 0.0980f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.2549f, 0.0980f, 0.0f,

        //E

        0.5f, 0.5f, 0.5f,  0.2549f, 0.0980f, 0.0f,
        0.5f, 0.5f, 0.0f,  0.2549f, 0.0980f, 0.0f,
        0.0f, 0.5f, 0.0f,  0.2549f, 0.0980f, 0.0f,
        0.0f, 0.5f, 0.5f,  0.2549f, 0.0980f, 0.0f,

        //F

        0.0f, 0.0f, 0.0f,  0.2549f, 0.0980f, 0.0f,
        0.5f, 0.0f, 0.0f,  0.2549f, 0.0980f, 0.0f,
        0.5f, 0.0f, 0.5f,0.2549f, 0.0980f, 0.0f,
        0.0f, 0.0f, 0.5f,  0.2549f, 0.0980f, 0.0f


    };

    float cube_vertices7[] = {

        //A
        0.0f, 0.0f, 0.0f, 0.5764f, 0.3411f, 0.1960f,
        0.5f, 0.0f, 0.0f, 0.5764f, 0.3411f, 0.1960f,
        0.5f, 0.5f, 0.0f, 0.5764f, 0.3411f, 0.1960f,
        0.0f, 0.5f, 0.0f, 0.5764f, 0.3411f, 0.1960f,

        //B

        0.5f, 0.0f, 0.0f,  0.5764f, 0.3411f, 0.1960f,
        0.5f, 0.5f, 0.0f, 0.5764f, 0.3411f, 0.1960f,
        0.5f, 0.0f, 0.5f,0.5764f, 0.3411f, 0.1960f,
        0.5f, 0.5f, 0.5f,0.5764f, 0.3411f, 0.1960f,

        //C

        0.0f, 0.0f, 0.5f, 0.5764f, 0.3411f, 0.1960f,
        0.5f, 0.0f, 0.5f,0.5764f, 0.3411f, 0.1960f,
        0.5f, 0.5f, 0.5f, 0.5764f, 0.3411f, 0.1960f,
        0.0f, 0.5f, 0.5f, 0.5764f, 0.3411f, 0.1960f,

        //D

        0.0f, 0.0f, 0.5f,  0.5764f, 0.3411f, 0.1960f,
        0.0f, 0.5f, 0.5f,  0.5764f, 0.3411f, 0.1960f,
        0.0f, 0.5f, 0.0f, 0.5764f, 0.3411f, 0.1960f,
        0.0f, 0.0f, 0.0f, 0.5764f, 0.3411f, 0.1960f,

        //E

        0.5f, 0.5f, 0.5f, 0.5764f, 0.3411f, 0.1960f,
        0.5f, 0.5f, 0.0f,  0.5764f, 0.3411f, 0.1960f,
        0.0f, 0.5f, 0.0f,  0.5764f, 0.3411f, 0.1960f,
        0.0f, 0.5f, 0.5f,  0.5764f, 0.3411f, 0.1960f,

        //F

        0.0f, 0.0f, 0.0f,  0.5764f, 0.3411f, 0.1960f,
        0.5f, 0.0f, 0.0f, 0.5764f, 0.3411f, 0.1960f,
        0.5f, 0.0f, 0.5f,0.5764f, 0.3411f, 0.1960f,
        0.0f, 0.0f, 0.5f, 0.5764f, 0.3411f, 0.1960f


    };

    float cube_vertices8[] = {

        //A
        0.0f, 0.0f, 0.0f, 0.9882f, 0.7882f, 0.6745f,
        0.5f, 0.0f, 0.0f, 0.9882f, 0.7882f, 0.6745f,
        0.5f, 0.5f, 0.0f, 0.9882f, 0.7882f, 0.6745f,
        0.0f, 0.5f, 0.0f, 0.9882f, 0.7882f, 0.6745f,

        //B

        0.5f, 0.0f, 0.0f, 0.9882f, 0.7882f, 0.6745f,
        0.5f, 0.5f, 0.0f, 0.9882f, 0.7882f, 0.6745f,
        0.5f, 0.0f, 0.5f, 0.9882f, 0.7882f, 0.6745f,
        0.5f, 0.5f, 0.5f, 0.9882f, 0.7882f, 0.6745f,

        //C

        0.0f, 0.0f, 0.5f, 0.9882f, 0.7882f, 0.6745f,
        0.5f, 0.0f, 0.5f, 0.9882f, 0.7882f, 0.6745f,
        0.5f, 0.5f, 0.5f, 0.9882f, 0.7882f, 0.6745f,
        0.0f, 0.5f, 0.5f, 0.9882f, 0.7882f, 0.6745f,

        //D

        0.0f, 0.0f, 0.5f, 0.9882f, 0.7882f, 0.6745f,
        0.0f, 0.5f, 0.5f, 0.9882f, 0.7882f, 0.6745f,
        0.0f, 0.5f, 0.0f, 0.9882f, 0.7882f, 0.6745f,
        0.0f, 0.0f, 0.0f, 0.9882f, 0.7882f, 0.6745f,

        //E

        0.5f, 0.5f, 0.5f, 0.9882f, 0.7882f, 0.6745f,
        0.5f, 0.5f, 0.0f,  0.9882f, 0.7882f, 0.6745f,
        0.0f, 0.5f, 0.0f,  0.9882f, 0.7882f, 0.6745f,
        0.0f, 0.5f, 0.5f,  0.9882f, 0.7882f, 0.6745f,

        //F

        0.0f, 0.0f, 0.0f,  0.9882f, 0.7882f, 0.6745f,
        0.5f, 0.0f, 0.0f, 0.9882f, 0.7882f, 0.6745f,
        0.5f, 0.0f, 0.5f, 0.9882f, 0.7882f, 0.6745f,
        0.0f, 0.0f, 0.5f, 0.9882f, 0.7882f, 0.6745f


    };

    float cube_vertices9[] = {

        //A
        0.0f, 0.0f, 0.0f,     0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,      0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f,      0.0f, 0.0f, 0.0f,

        //B

        0.5f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,      0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.5f,      0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f,      0.0f, 0.0f, 0.0f,

        //C

        0.0f, 0.0f, 0.5f,      0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.5f,      0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f,      0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.5f,      0.0f, 0.0f, 0.0f,

        //D

        0.0f, 0.0f, 0.5f,      0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.5f,      0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f,      0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,

        //E

        0.5f, 0.5f, 0.5f,      0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,       0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f,      0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.5f,       0.0f, 0.0f, 0.0f,

        //F

        0.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.5f,      0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.5f,      0.0f, 0.0f, 0.0f


    };

    float cube_vertices10[] = {

        //A
        0.0f, 0.0f, 0.0f,     0.9450f, 0.6235f, 0.4784f,
        0.5f, 0.0f, 0.0f,       0.9450f, 0.6235f, 0.4784f,
        0.5f, 0.5f, 0.0f,      0.9450f, 0.6235f, 0.4784f,
        0.0f, 0.5f, 0.0f,       0.9450f, 0.6235f, 0.4784f,

        //B

        0.5f, 0.0f, 0.0f,      0.9450f, 0.6235f, 0.4784f,
        0.5f, 0.5f, 0.0f,    0.9450f, 0.6235f, 0.4784f,
        0.5f, 0.0f, 0.5f,      0.9450f, 0.6235f, 0.4784f,
        0.5f, 0.5f, 0.5f,     0.9450f, 0.6235f, 0.4784f,

        //C

        0.0f, 0.0f, 0.5f,     0.9450f, 0.6235f, 0.4784f,
        0.5f, 0.0f, 0.5f,    0.9450f, 0.6235f, 0.4784f,
        0.5f, 0.5f, 0.5f,     0.9450f, 0.6235f, 0.4784f,
        0.0f, 0.5f, 0.5f,    0.9450f, 0.6235f, 0.4784f,

        //D

        0.0f, 0.0f, 0.5f,    0.9450f, 0.6235f, 0.4784f,
        0.0f, 0.5f, 0.5f,     0.9450f, 0.6235f, 0.4784f,
        0.0f, 0.5f, 0.0f,     0.9450f, 0.6235f, 0.4784f,
        0.0f, 0.0f, 0.0f,   0.9450f, 0.6235f, 0.4784f,

        //E

        0.5f, 0.5f, 0.5f,      0.9450f, 0.6235f, 0.4784f,
        0.5f, 0.5f, 0.0f,     0.9450f, 0.6235f, 0.4784f,
        0.0f, 0.5f, 0.0f,     0.9450f, 0.6235f, 0.4784f,
        0.0f, 0.5f, 0.5f,    0.9450f, 0.6235f, 0.4784f,

        //F

        0.0f, 0.0f, 0.0f,    0.9450f, 0.6235f, 0.4784f,
        0.5f, 0.0f, 0.0f,   0.9450f, 0.6235f, 0.4784f,
        0.5f, 0.0f, 0.5f,    0.9450f, 0.6235f, 0.4784f,
        0.0f, 0.0f, 0.5f,     0.9450f, 0.6235f, 0.4784f,


    };

    float cube_vertices11[] = {

        //A
        0.0f, 0.0f, 0.0f,     0.8235f, 0.6470f, 0.4274f,
        0.5f, 0.0f, 0.0f,   0.8235f, 0.6470f, 0.4274f,
        0.5f, 0.5f, 0.0f,     0.8235f, 0.6470f, 0.4274f,
        0.0f, 0.5f, 0.0f,      0.8235f, 0.6470f, 0.4274f,

        //B

        0.5f, 0.0f, 0.0f,    0.8235f, 0.6470f, 0.4274f,
        0.5f, 0.5f, 0.0f,   0.8235f, 0.6470f, 0.4274f,
        0.5f, 0.0f, 0.5f,     0.8235f, 0.6470f, 0.4274f,
        0.5f, 0.5f, 0.5f,   0.8235f, 0.6470f, 0.4274f,

        //C

        0.0f, 0.0f, 0.5f,     0.8235f, 0.6470f, 0.4274f,
        0.5f, 0.0f, 0.5f,   0.8235f, 0.6470f, 0.4274f,
        0.5f, 0.5f, 0.5f,    0.8235f, 0.6470f, 0.4274f,
        0.0f, 0.5f, 0.5f,     0.8235f, 0.6470f, 0.4274f,

        //D

        0.0f, 0.0f, 0.5f,   0.8235f, 0.6470f, 0.4274f,
        0.0f, 0.5f, 0.5f,    0.8235f, 0.6470f, 0.4274f,
        0.0f, 0.5f, 0.0f,  0.8235f, 0.6470f, 0.4274f,
        0.0f, 0.0f, 0.0f,   0.8235f, 0.6470f, 0.4274f,

        //E

        0.5f, 0.5f, 0.5f,   0.8235f, 0.6470f, 0.4274f,
        0.5f, 0.5f, 0.0f,   0.8235f, 0.6470f, 0.4274f,
        0.0f, 0.5f, 0.0f,    0.8235f, 0.6470f, 0.4274f,
        0.0f, 0.5f, 0.5f,   0.8235f, 0.6470f, 0.4274f,

        //F

        0.0f, 0.0f, 0.0f,    0.8235f, 0.6470f, 0.4274f,
        0.5f, 0.0f, 0.0f,    0.8235f, 0.6470f, 0.4274f,
        0.5f, 0.0f, 0.5f,    0.8235f, 0.6470f, 0.4274f,
        0.0f, 0.0f, 0.5f,    0.8235f, 0.6470f, 0.4274f,


    };


    float cube_vertices12[] = {

        //A
        0.0f, 0.0f, 0.0f,     0.5333f, 0.8078f, 0.9215f,
        0.5f, 0.0f, 0.0f,    0.5333f, 0.8078f, 0.9215f,
        0.5f, 0.5f, 0.0f,     0.5333f, 0.8078f, 0.9215f,
        0.0f, 0.5f, 0.0f,    0.5333f, 0.8078f, 0.9215f,

        //B

        0.5f, 0.0f, 0.0f,   0.5333f, 0.8078f, 0.9215f,
        0.5f, 0.5f, 0.0f,    0.5333f, 0.8078f, 0.9215f,
        0.5f, 0.0f, 0.5f,    0.5333f, 0.8078f, 0.9215f,
        0.5f, 0.5f, 0.5f,   0.5333f, 0.8078f, 0.9215f,

        //C

        0.0f, 0.0f, 0.5f,    0.5333f, 0.8078f, 0.9215f,
        0.5f, 0.0f, 0.5f,  0.5333f, 0.8078f, 0.9215f,
        0.5f, 0.5f, 0.5f,    0.5333f, 0.8078f, 0.9215f,
        0.0f, 0.5f, 0.5f,    0.5333f, 0.8078f, 0.9215f,

        //D

        0.0f, 0.0f, 0.5f,  0.5333f, 0.8078f, 0.9215f,
        0.0f, 0.5f, 0.5f,   0.5333f, 0.8078f, 0.9215f,
        0.0f, 0.5f, 0.0f,  0.5333f, 0.8078f, 0.9215f,
        0.0f, 0.0f, 0.0f,   0.5333f, 0.8078f, 0.9215f,

        //E

        0.5f, 0.5f, 0.5f,   0.5333f, 0.8078f, 0.9215f,
        0.5f, 0.5f, 0.0f,   0.5333f, 0.8078f, 0.9215f,
        0.0f, 0.5f, 0.0f,   0.5333f, 0.8078f, 0.9215f,
        0.0f, 0.5f, 0.5f,   0.5333f, 0.8078f, 0.9215f,

        //F

        0.0f, 0.0f, 0.0f,     0.5333f, 0.8078f, 0.9215f,
        0.5f, 0.0f, 0.0f,  0.5333f, 0.8078f, 0.9215f,
        0.5f, 0.0f, 0.5f,    0.5333f, 0.8078f, 0.9215f,
        0.0f, 0.0f, 0.5f,   0.5333f, 0.8078f, 0.9215f,


    };

  


    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };
    /*unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        1, 2, 6,
        6, 5, 1,

        5, 6, 7,
        7 ,4, 5,

        4, 7, 3,
        3, 0, 4,

        6, 2, 3,
        3, 7, 6,

        1, 5, 4,
        4, 0, 1
    };*/
    /*float cube_vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };*/
    // world space positions of our cubes
    /*glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };*/

    //1st color for 
    unsigned int VBO1, VAO1, EBO1;
    glGenVertexArrays(1, &VAO1); 
    glGenBuffers(1, &VBO1);
    glGenBuffers(1, &EBO1);

    glBindVertexArray(VAO1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices1), cube_vertices1, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);


    //2nd color

    unsigned int VBO2, VAO2, EBO2;
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);
    glGenBuffers(1, &EBO2);

    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices2), cube_vertices2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


   
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

   
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);


    //3rd color

    unsigned int VBO3, VAO3, EBO3;
    glGenVertexArrays(1, &VAO3);
    glGenBuffers(1, &VBO3);
    glGenBuffers(1, &EBO3);

    glBindVertexArray(VAO3);

    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices3), cube_vertices3, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


  
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);



    //4th color

    unsigned int VBO4, VAO4, EBO4;
    glGenVertexArrays(1, &VAO4);
    glGenBuffers(1, &VBO4);
    glGenBuffers(1, &EBO4);

    glBindVertexArray(VAO4);

    glBindBuffer(GL_ARRAY_BUFFER, VBO4);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices4), cube_vertices4, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO4);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


   
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // 5th color

    unsigned int VBO5, VAO5, EBO5;
    glGenVertexArrays(1, &VAO5);
    glGenBuffers(1, &VBO5);
    glGenBuffers(1, &EBO5);

    glBindVertexArray(VAO5);

    glBindBuffer(GL_ARRAY_BUFFER, VBO5);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices5), cube_vertices5, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO5);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

   
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    //6th color

    unsigned int VBO6, VAO6, EBO6;
    glGenVertexArrays(1, &VAO6);
    glGenBuffers(1, &VBO6);
    glGenBuffers(1, &EBO6);

    glBindVertexArray(VAO6);

    glBindBuffer(GL_ARRAY_BUFFER, VBO6);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices6), cube_vertices6, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO6);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

  
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    //7th color

    unsigned int VBO7, VAO7, EBO7;
    glGenVertexArrays(1, &VAO7);
    glGenBuffers(1, &VBO7);
    glGenBuffers(1, &EBO7);

    glBindVertexArray(VAO7);

    glBindBuffer(GL_ARRAY_BUFFER, VBO7);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices7), cube_vertices7, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO7);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    //8th color

    unsigned int VBO8, VAO8, EBO8;
    glGenVertexArrays(1, &VAO8);
    glGenBuffers(1, &VBO8);
    glGenBuffers(1, &EBO8);

    glBindVertexArray(VAO8);

    glBindBuffer(GL_ARRAY_BUFFER, VBO8);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices8), cube_vertices8, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO8);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    //9th color

   

    unsigned int VBO9, VAO9, EBO9;
    glGenVertexArrays(1, &VAO9);
    glGenBuffers(1, &VBO9);
    glGenBuffers(1, &EBO9);

    glBindVertexArray(VAO9);

    glBindBuffer(GL_ARRAY_BUFFER, VBO9);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices9), cube_vertices9, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO9);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    //10th color

    unsigned int VBO10, VAO10, EBO10;
    glGenVertexArrays(1, &VAO10);
    glGenBuffers(1, &VBO10);
    glGenBuffers(1, &EBO10);

    glBindVertexArray(VAO10);

    glBindBuffer(GL_ARRAY_BUFFER, VBO10);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices10), cube_vertices10, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO10);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);


    //11th color

    unsigned int VBO11, VAO11, EBO11;
    glGenVertexArrays(1, &VAO11);
    glGenBuffers(1, &VBO11);
    glGenBuffers(1, &EBO11);

    glBindVertexArray(VAO11);

    glBindBuffer(GL_ARRAY_BUFFER, VBO11);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices11), cube_vertices11, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO11);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    //12th color

    unsigned int VBO12, VAO12, EBO12;
    glGenVertexArrays(1, &VAO12);
    glGenBuffers(1, &VBO12);
    glGenBuffers(1, &EBO12);

    glBindVertexArray(VAO12);

    glBindBuffer(GL_ARRAY_BUFFER, VBO12);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices12), cube_vertices12, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO12);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);







    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    //ourShader.use();

    // render loop
    // -----------


    float rotate = 0.0f;
  
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        ourShader.setMat4("view", view);

        //chair start

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;



        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X-2.0f, translate_Y-0.15f, translate_Z+2.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, 0.25f, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO7);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //paya start
      

        // Modelling Transformation
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X-2.0f, -0.5f, translate_Z+2.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 0.7f, 0.25f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO7);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //2nd paya

        // Modelling Transformation
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.375-2.0f, -0.5f, translate_Z+2.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 0.7f, 0.25f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO7);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //3rd paya
        

        // Modelling Transformation
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0-2.0f, -0.5f, 0.375f+2.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 0.7f, 0.25f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO7);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //4th paya

        // Modelling Transformation
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.375-2.0f, -0.5f, 0.375f+2.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 0.7f, 0.25f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO7);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //uporer paya


        // Modelling Transformation
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0-2.0f, 0.125f-0.15f, translate_Z+2.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 1.0f, 0.25f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO7);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //2nd uporer paya


        // Modelling Transformation
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.375-2.0f, 0.125f-0.15f, translate_Z+2.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 1.0f, 0.25f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO7);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //parallel uporer paya

        // Modelling Transformation
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0-2.0f, 0.5f-0.15f, translate_Z+2.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.25f, 0.25f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO7);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //chair done

        //table start ,pataton

  
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.25-2.0f, 0.3f-0.25f, 0.8f+2.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.25f, 1.2f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO5);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //table pataton er uporer part


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.25-2.0f, 0.448f-0.25f, 0.8f+2.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, -0.05f, 1.2f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO1);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //table paya back right

        // Modelling Transformation
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.25-2.0f, -0.5f, 0.8f+2.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 1.1f, 0.25f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO5);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //table paya front right

        // Modelling Transformation
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.25-2.0f, -0.5f, 1.275f+2.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 1.1f, 0.25f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO5);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //table paya back left

        // Modelling Transformation
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.625-2.0f, -0.5f, 0.8f+2.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 1.1f, 0.25f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO5);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



        //table paya front left


        // Modelling Transformation
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.625-2.0f, -0.5f, 1.275f+2.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 1.1f, 0.25f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO5);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //table done

        //khat start

        //matress 

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.5-0.5f, translate_Y, -0.04f-0.9f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.25f, 4.0f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO2);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //pataton


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.5-0.5f, -0.125f, translate_Z-0.9f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.25f, 4.0f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //front left paya

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.5-0.5f, -0.5f, 1.875f-0.9f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 1.0f, 0.25f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //front right paya

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.625-0.5f, -0.5f, 1.875f-0.9f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 1.0f, 0.25f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //back left paya

        

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.5-0.5f, -0.5f, -0.125f-0.9f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 1.0f, 0.25f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //back right paya

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.625-0.5f, -0.5f, -0.125f-0.9f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 1.0f, 0.25f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //khater matha
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.5-0.5f, -0.125f, -0.125-0.9f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 1.2f, 0.125f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //almari start



        //nicher pataton

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5-4.0f , -0.5f, -1.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.8f, 0.1f, 1.5f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO4);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //ba diker pataton

        translateMatrix = glm::translate(identityMatrix, glm::vec3(- 0.45-4.0f, -0.45f, -1.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.8f, 0.1f, 1.5f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO4);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //dan diker pataton

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.9-4.0f, -0.45f, -1.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.8f, 0.1f, 1.5f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO4);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //uporer pataton

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5 - 4.0f, 0.92f, -1.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.8f, 0.1f, 1.5f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO4);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //majher pataton

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.22f - 4.0f, -0.45f, -1.0+0.15f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.8f, 0.1f, 1.3f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO4);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //door right


        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.22f - 4.0f, -0.45f, 0.75f-1.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.8f, 0.1f, 1.26f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //door left


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.45f - 4.0f, -0.45f, 0.75f-1.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.8f, 0.1f, 1.25f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //pichher pataton 

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.45 - 4.0f, 0.935f, -1.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.6f, 0.1f, 2.75f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO4);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //almari done
        
        //side almari start

        //nicher pataton

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5 - 0.3f, -0.5f, 0.3-1.3f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.1f, 1.5f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO4);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //niche theke 2nd pataton


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5 - 0.3f, -0.2f, 0.3f-1.3f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.1f, 1.5f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO4);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //niche theke 3rd pataton


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5 - 0.3f, 0.1f, 0.3f-1.3f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.1f, 1.5f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO4);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //uporer pataton


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5 - 0.3f, 0.4f, 0.3f-1.3f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.1f, 1.5f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO4);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //left pataton

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5 - 0.3f, -0.5f, 0.3f-1.3f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.9f, 0.1f, 1.5f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO4);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //right pataton

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25f - 0.3f, -0.5f, 0.3f-1.3f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.9f, 0.1f, 1.5f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO4);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //NICHER DRAWER

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5 - 0.3f, -0.45f, 1.05f-1.3f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.4f, 0.1f, 0.5f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //MIDDLE DRAWER

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5 - 0.3f, -0.15f, 1.05f-1.3f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.4f, 0.1f, 0.5f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //uporer drawer

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5 - 0.3f, 0.15f, 1.05f-1.3f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.4f, 0.1f, 0.5f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //side table pichher pataton baki




        //floor

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.0f, -0.55f, -1.5f+0.3f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.8f, 0.1f, 10.5f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO11);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //chhaad
        /*
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.0f, 4.0f, -1.5f + 0.3f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.8f, 0.1f, 12.5f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO11);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        */


        //wall



        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.0f, -0.55f, -1.5f+0.3f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.8f, 0.1f, 12.5f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO8);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //wall



        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.0f, -0.55f, -1.5f+0.3f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(12.8f, 0.1f, 10.5f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO10);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //monitor pataton


        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.1f -2.0f, 0.448f-0.223f, 1.0f+2.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.7f, -0.05f, 0.7f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO9);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //monitor device

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f -2.0f, 0.448f - 0.223f, 1.0f+2.7f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.1f, 1.0f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO9);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f - 2.0f, 0.448f - 0.223f, 1.0f + 2.65f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.01f, 1.0f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO12);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //ayna start



        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X - 3.0f-1.5f, translate_Y-0.5f, translate_Z + 3.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.25f, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //drawer

        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X - 3.0f-1.5f, translate_Y - 0.375f, translate_Z + 3.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.25f, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO4);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //drawer



        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X - 3.0f-1.5f, translate_Y-0.25f, translate_Z + 3.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.25f, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO4);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



        //drawer
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X - 3.0f-1.5f, translate_Y - 0.125f, translate_Z + 3.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.25f, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO4);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X - 3.0f-1.5f, translate_Y+0.0f, translate_Z + 3.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.25f, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



        //ayna part

        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X - 2.875f-1.5f, translate_Y + 0.125f, translate_Z + 2.7f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.25f, 1.3f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X - 2.875f+0.025f-1.5f, translate_Y + 0.125f, translate_Z + 2.7f+0.025f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.9f, 0.05f, 1.2f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO12);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X - 3.0f-1.5f, translate_Y - 0.5f, translate_Z + 3.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.25f, 0.25f, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X - 3.0f-1.5f, translate_Y - 0.5f, translate_Z + 2.375f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.25f, 0.25f, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);




        //fan start

        glm::mat4 tMatrix, tinvMatrix, rotateY2Matrix;


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.7f, 3.7f, 1.2f));
        tMatrix = glm::translate(identityMatrix, glm::vec3(-0.1625f, -0.0625f, -0.1625f));
        tinvMatrix = glm::translate(identityMatrix, glm::vec3(+0.1625f, +0.0625f, +0.1625f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotate), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.65f, 0.25f, 0.65f));
        model = translateMatrix * tinvMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * tMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.7f + 0.08125f, 3.7f, 3.2f - 0.325f-2.0f));
        tMatrix = glm::translate(identityMatrix, glm::vec3(-0.08125f, -0.0625f, -0.4875f));
        tinvMatrix = glm::translate(identityMatrix, glm::vec3(+0.08125f, +0.0625f, +0.4875f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotate), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.325f, 0.25f, 0.65 * 3.0f));
        model = translateMatrix * tinvMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * tMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.7f + 0.08125f, 3.7f, 3.2f - 0.325f-2.0f));
        tMatrix = glm::translate(identityMatrix, glm::vec3(-0.08125f, -0.0625f, -0.4875f));
        tinvMatrix = glm::translate(identityMatrix, glm::vec3(+0.08125f, +0.0625f, +0.4875f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateY2Matrix = glm::rotate(identityMatrix, glm::radians(rotate), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.325f, 0.25f, 0.65 * 3.0f));
        model = translateMatrix * tinvMatrix * rotateXMatrix * rotateY2Matrix * rotateYMatrix * rotateZMatrix * tMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.7f+0.1375f, 3.7f+0.125f, 1.2f+0.1375f));
        tMatrix = glm::translate(identityMatrix, glm::vec3(-0.025f, 0.0f, -0.025f));
        tinvMatrix = glm::translate(identityMatrix, glm::vec3(+0.025f, 0.0f, +0.025f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotate), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.2f, 0.1f));
        model = translateMatrix * tinvMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * tMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



        if (fan_on == true)
        {
            rotate += 1;
        }




        //table lamp



        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5 - 0.1f, 0.4+0.01f, 0.3f - 1.1f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.65f, 0.25f, 0.65f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO6);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5 - 0.1f+0.14f, 0.4 + 0.01f, 0.3f - 1.1f+0.14f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 0.1f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO6);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5 - 0.1f, 0.4 + 0.01f+0.5f, 0.3f - 1.1f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.65f, 1.0f, 0.65f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
        glBindVertexArray(VAO1);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        














        // render boxes
        //for (unsigned int i = 0; i < 10; i++)
        //{
        //    // calculate the model matrix for each object and pass it to shader before drawing
        //    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //    model = glm::translate(model, cubePositions[i]);
        //    float angle = 20.0f * i;
        //    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        //    ourShader.setMat4("model", model);

        //    glDrawArrays(GL_TRIANGLES, 0, 36);
        //}

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO1);
    glDeleteBuffers(1, &EBO1);

    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO2);
    glDeleteBuffers(1, &EBO2);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(YAW_L, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(YAW_R, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(PITCH_U, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(PITCH_D, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(ROLL_F, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(ROLL_B, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        if (fan_on == false)
        {
            fan_on = true;
        }
      
    }
    if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
        
        if (fan_on == true)
        {
            fan_on = false;
        }

    }


    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 1;
        else if (rotateAxis_Y) rotateAngle_Y -= 1;
        else rotateAngle_Z -= 1;
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.01;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.01;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.01;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.01;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.01;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.01;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.01;
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.01;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.01;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.01;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.01;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.01;

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        rotateAngle_X += 1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        rotateAngle_Y += 1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotateAngle_Z += 1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        eyeX += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        eyeX -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        eyeZ += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        eyeZ -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        eyeY += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        eyeY -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    /*
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        lookAtX += 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        lookAtX -= 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        lookAtY += 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        lookAtY -= 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        lookAtZ += 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        lookAtZ -= 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }*/
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        basic_camera.changeViewUpVector(glm::vec3(1.0f, 0.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
    {
        basic_camera.changeViewUpVector(glm::vec3(0.0f, 1.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
    {
        basic_camera.changeViewUpVector(glm::vec3(0.0f, 0.0f, 1.0f));
    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
