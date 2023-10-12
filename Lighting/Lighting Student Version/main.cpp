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
#include "pointLight.h"
//#include "spotLight.h"
#include "sphere.h"

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void chair(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void table(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void table2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void longtable(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void floor(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void wall1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void wall2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void chaad(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

// camera
Camera camera(glm::vec3(0.0f, 1.1f, 5.2f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);


// positions of the point lights
glm::vec3 

 pointLightPositions[] = {

    glm::vec3(-1.75f, 4.0f, 0.8f + 2.5f),
    glm::vec3(3.25f,  4.0f,  3.3f),
    glm::vec3(-1.5f,  4.0f,  0.0f),
    glm::vec3(-1.0f,  4.0f,  0.0f),
    glm::vec3(-0.5f,  4.0f,  0.0f),
    glm::vec3(0.0f,  4.0f,  0.0f)
};

 
PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
PointLight pointlight2(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);
PointLight pointlight3(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    3       // light number
);
PointLight pointlight4(

    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    4       // light number
);
/*
SpotLight spotlight1(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.0f,-1.0f,0.0f,  //direction
    0.5f,   //cos_theta
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
*/



// light settings
bool pointlight1on = true;
bool pointlight2on = true;
bool directionallighton = true;
bool spotlight1on = true;
bool spotlight2on = true;
bool spotlight3on = true;
bool spotlight4on = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;


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
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

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
    //Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.25f,
        0.5f, 0.0f, 0.0f,  0.0f, 0.0f, -0.25f,
        0.5f, 0.5f, 0.0f,  0.0f, 0.0f, -0.25f,
        0.0f, 0.5f, 0.0f,  0.0f, 0.0f, -0.25f,

        0.5f, 0.0f, 0.0f, 0.25f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 0.25f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.5f, 0.25f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.25f, 0.0f, 0.0f,

         0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.25f,
        0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.25f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.25f,
        0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.25f,

   

        0.0f, 0.0f, 0.5f, -0.25f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.5f, -0.25f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f, -0.25f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -0.25f, 0.0f, 0.0f,

     

        0.5f, 0.5f, 0.5f, 0.0f, 0.25f, 0.0f,
        0.5f, 0.5f, 0.0f, 0.0f, 0.25f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.25f, 0.0f,
        0.0f, 0.5f, 0.5f, 0.0f, 0.25f, 0.0f,


        0.0f, 0.0f, 0.0f, 0.0f, -0.25f, 0.0f,
        0.5f, 0.0f, 0.0f, 0.0f, -0.25f, 0.0f,
        0.5f, 0.0f, 0.5f, 0.0f, -0.25f, 0.0f,
        0.0f, 0.0f, 0.5f, 0.0f, -0.25f, 0.0f
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

    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Sphere sphere = Sphere();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    //ourShader.use();
    //lightingShader.use();

    // render loop
    // -----------
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
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);

        if (directionallighton)
        {
            lightingShader.setBool("directionallighton", true);
        }
        else
        {
            lightingShader.setBool("directionallighton", false);
        }

        if (spotlight1on)
        {
            lightingShader.setBool("spotlight1on", true);
        }
        else
        {
            lightingShader.setBool("spotlight1on", false);
        }

        if (spotlight2on)
        {
            lightingShader.setBool("spotlight2on", true);
        }
        else
        {
            lightingShader.setBool("spotlight2on", false);
        }

        if (spotlight3on)
        {
            lightingShader.setBool("spotlight3on", true);
        }
        else
        {
            lightingShader.setBool("spotlight3on", false);
        }

        if (spotlight4on)
        {
            lightingShader.setBool("spotlight4on", true);
        }
        else
        {
            lightingShader.setBool("spotlight4on", false);
        }

        if (pointlight1on)
        {
            lightingShader.setBool("pointlight1on", true);
        }
        else
        {
            lightingShader.setBool("pointlight1on", false);
        }

        if (pointlight2on)
        {
            lightingShader.setBool("pointlight2on", true);
        }
        else
        {
            lightingShader.setBool("pointlight2on", false);
        }

        // point light 1
        pointlight1.setUpPointLight(lightingShader);
        // point light 2
        pointlight2.setUpPointLight(lightingShader);
        // point light 3
        pointlight3.setUpPointLight(lightingShader);
        // point light 4
        pointlight4.setUpPointLight(lightingShader);

        //spotlight1
        //spotlight1.setUpSpotLight(lightingShader);


        

        lightingShader.setVec3("spotlight[0].position", -1.5f, 4.0f, 0.0f);
        lightingShader.setVec3("spotlight[0].direction", 0.0f, -1.0f, 0.0f);
        lightingShader.setFloat("spotlight[0].k_c ", 1.0f);
        lightingShader.setFloat("spotlight[0].k_l", 0.09f);
        lightingShader.setFloat("spotlight[0].k_q", 0.032f);
        lightingShader.setFloat("spotlight[0].cos_theta", glm::cos(glm::radians(5.5f)));
        lightingShader.setVec3("spotlight[0].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setVec3("spotlight[0].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("spotlight[0].specular", 1.0f, 1.0f, 1.0f);

        //spotlight2

        lightingShader.setVec3("spotlight[1].position", -1.0f, 4.0f, 0.0f);
        lightingShader.setVec3("spotlight[1].direction", 0.0f, -1.0f, 0.0f);
        lightingShader.setFloat("spotlight[1].k_c ", 1.0f);
        lightingShader.setFloat("spotlight[1].k_l", 0.09f);
        lightingShader.setFloat("spotlight[1].k_q", 0.032f);
        lightingShader.setFloat("spotlight[1].cos_theta", glm::cos(glm::radians(5.5f)));
        lightingShader.setVec3("spotlight[1].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setVec3("spotlight[1].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("spotlight[1].specular", 1.0f, 1.0f, 1.0f);

        //spotlight3

        lightingShader.setVec3("spotlight[2].position", -0.5f, 4.0f, 0.0f);
        lightingShader.setVec3("spotlight[2].direction", 0.0f, -1.0f, 0.0f);
        lightingShader.setFloat("spotlight[2].k_c ", 1.0f);
        lightingShader.setFloat("spotlight[2].k_l", 0.09f);
        lightingShader.setFloat("spotlight[2].k_q", 0.032f);
        lightingShader.setFloat("spotlight[2].cos_theta", glm::cos(glm::radians(5.5f)));
        lightingShader.setVec3("spotlight[2].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setVec3("spotlight[2].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("spotlight[2].specular", 1.0f, 1.0f, 1.0f);

        //spotlight4


        lightingShader.setVec3("spotlight[3].position", -0.0f, 4.0f, 0.0f);
        lightingShader.setVec3("spotlight[3].direction", 0.0f, -1.0f, 0.0f);
        lightingShader.setFloat("spotlight[3].k_c ", 1.0f);
        lightingShader.setFloat("spotlight[3].k_l", 0.09f);
        lightingShader.setFloat("spotlight[3].k_q", 0.032f);
        lightingShader.setFloat("spotlight[3].cos_theta", glm::cos(glm::radians(5.5f)));
        lightingShader.setVec3("spotlight[3].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setVec3("spotlight[3].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("spotlight[3].specular", 1.0f, 1.0f, 1.0f);

        //directional light

        lightingShader.setVec3("directionallight.direction",0.5f,-3.0f,-3.0f);
        lightingShader.setVec3("directionallight.ambient", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("directionallight.diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("directionallight.specular", 1.0f, 1.0f, 1.0f);
        


        // activate shader
        lightingShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        // glm::mat4 view = basic_camera.createViewMatrix();
        lightingShader.setMat4("view", view);

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateY2Matrix ,rotateZMatrix, scaleMatrix, model1,model2,model3,model4,model5,model6,model7,model8,model9,model10,model11;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
    
        model1= translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        lightingShader.setMat4("model", model1);


        chair(cubeVAO, lightingShader, model1);

        table(cubeVAO, lightingShader, model1);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.5f, translate_Y, 7.2f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model2 = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", model2);

        chair(cubeVAO, lightingShader, model2);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.0f, translate_Y, translate_Z));

        model3 = translateMatrix * model1;

        lightingShader.setMat4("model", model3);


        chair(cubeVAO, lightingShader, model3);

        table(cubeVAO, lightingShader, model3);

        model4 = translateMatrix * model2;

        lightingShader.setMat4("model", model4);

        chair(cubeVAO, lightingShader, model4);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, translate_Y, -1.0));


        model5 = translateMatrix * model1;

        lightingShader.setMat4("model", model5);

        floor(cubeVAO, lightingShader, model5);

        wall1(cubeVAO, lightingShader, model5);

        wall2(cubeVAO, lightingShader, model5);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.3f, -0.6f, -0.4f));

        model6 = translateMatrix * model1;
        lightingShader.setMat4("model", model6);

        table2(cubeVAO, lightingShader, model6);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 6.0f, -1.0));


        model7 = translateMatrix * model1;

        lightingShader.setMat4("model", model7);

        floor(cubeVAO, lightingShader, model7);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.75f, 0.0f, -4.0f));

        model8= translateMatrix * model1;

        lightingShader.setMat4("model", model8);

        longtable(cubeVAO, lightingShader, model8);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.0f, 0.0f, 0.0f));

        model9 = translateMatrix * model6;
        lightingShader.setMat4("model", model9);

        table2(cubeVAO, lightingShader, model9);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, translate_Y, -3.6f));

        model10 = translateMatrix * model1;

        lightingShader.setMat4("model", model10);

        chair(cubeVAO, lightingShader, model10);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, translate_Y, -3.6f));

        model11 = translateMatrix * model2;

        lightingShader.setMat4("model", model11);

        chair(cubeVAO, lightingShader, model11);



        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.25f, translate_Y, 0.0f));

        model10 = translateMatrix * model10;

        lightingShader.setMat4("model", model10);

        chair(cubeVAO, lightingShader, model10);

        model11 = translateMatrix * model11;

        lightingShader.setMat4("model", model11);

        chair(cubeVAO, lightingShader, model11);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.25f, translate_Y, 0.0f));

        model10 = translateMatrix * model10;

        lightingShader.setMat4("model", model10);

        chair(cubeVAO, lightingShader, model10);

        model11 = translateMatrix * model11;

        lightingShader.setMat4("model", model11);

        chair(cubeVAO, lightingShader, model11);



        //glBindVertexArray(cubeVAO);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        /*
        float xyz = 1.2f;
        
        for (unsigned int i = 0; i < 500; i++)
        {
            xyz = xyz - 0.001f;
            glm::mat4 modelForSphere = glm::mat4(1.0f);
            modelForSphere = glm::translate(model1, glm::vec3(1.5f, xyz, 0.5f));
            modelForSphere = glm::scale(modelForSphere, glm::vec3(0.35f, 0.005f, 0.35f));
            sphere.drawSphere(lightingShader, modelForSphere);
        }
        */


        

        // also draw the lamp object(s)
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        glBindVertexArray(lightCubeVAO);


        for (unsigned int i = 2; i < 6; i++)
        {
            model1 = glm::mat4(1.0f);
            model1 = glm::translate(model1, pointLightPositions[i]);
            model1 = glm::scale(model1, glm::vec3(0.2f, 0.2f, 0.2f)); // Make it a smaller cube
            ourShader.setMat4("model", model1);
            ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightCubeVAO);
       
        
        for (unsigned int i = 0; i < 2; i++)
        {
            model1 = glm::mat4(1.0f);
            model1 = glm::translate(model1, pointLightPositions[i]);
            model1 = glm::scale(model1, glm::vec3(0.2f,1.0f,0.2f)); // Make it a smaller cube
            ourShader.setMat4("model", model1);
            ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            //glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setVec3("material.emmisive", glm::vec3(r*0.1, g*0.1, b*0.0));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float baseHeight = 0.3;
    float width = 1;
    float length = 2;
    float pillowWidth = 0.3;
    float pillowLength = 0.15;
    float blanketWidth = 0.8;
    float blanketLength = 0.7;
    float headHeight = 0.6;

    //base
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //foam
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, baseHeight, 0));
    scale = glm::scale(model, glm::vec3(width, 0.06, length));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.804, 0.361, 0.361);

    //pillow 1
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3((width / 2) - (0.1 + pillowWidth / 2), baseHeight + 1 * 0.06, (length / 2) - (0.025 + pillowWidth / 2)));
    scale = glm::scale(model, glm::vec3(pillowWidth, 0.04, pillowLength));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);

    //pillow 2
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3((-width / 2) + (0.1 + pillowWidth / 2), baseHeight + 1 * 0.06, (length / 2) - (0.025 + pillowWidth / 2)));
    scale = glm::scale(model, glm::vec3(pillowWidth, 0.04, pillowLength));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);

    //blanket
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, baseHeight + 1 * 0.06, -(length / 2 - 0.025) + blanketLength / 2));
    scale = glm::scale(model, glm::vec3(blanketWidth, 0.015, blanketLength));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.541, 0.169, 0.886);

    //head
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, 0, (length / 2 - 0.02 / 2) + 0.02));
    scale = glm::scale(model, glm::vec3(width, headHeight, 0.02));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

}

void chair(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)

{
    //chair start

        // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;



    translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X - 2.0f, translate_Y - 0.15f, translate_Z + 2.5f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, 0.25f, scale_Z));
    model = alTogether*translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //lightingShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    drawCube(cubeVAO, lightingShader, model, 0.2784, 0.1843, 0.0901);
    


    //paya start


    // Modelling Transformation
    translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X - 2.0f, -0.5f, translate_Z + 2.5f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 0.7f, 0.25f));
    model = alTogether * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //lightingShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    drawCube(cubeVAO, lightingShader, model, 0.3176, 0.2117, 0.1019);


    //2nd paya

    // Modelling Transformation
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.375 - 2.0f, -0.5f, translate_Z + 2.5f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 0.7f, 0.25f));
    model = alTogether * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //lightingShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    drawCube(cubeVAO, lightingShader, model, 0.3176, 0.2117, 0.1019);

    //3rd paya


    // Modelling Transformation
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 - 2.0f, -0.5f, 0.375f + 2.5f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 0.7f, 0.25f));
    model = alTogether * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //lightingShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    drawCube(cubeVAO, lightingShader, model, 0.3176, 0.2117, 0.1019);


    //4th paya

    // Modelling Transformation
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.375 - 2.0f, -0.5f, 0.375f + 2.5f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 0.7f, 0.25f));
    model = alTogether * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //lightingShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    drawCube(cubeVAO, lightingShader, model, 0.3176, 0.2117, 0.1019);

    //uporer paya


    // Modelling Transformation
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 - 2.0f, 0.125f - 0.15f, translate_Z + 2.5f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 1.0f, 0.25f));
    model = alTogether * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //lightingShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    drawCube(cubeVAO, lightingShader, model, 0.2784, 0.1843, 0.0901);


    //2nd uporer paya


    // Modelling Transformation
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.375 - 2.0f, 0.125f - 0.15f, translate_Z + 2.5f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 1.0f, 0.25f));
    model = alTogether * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //lightingShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    drawCube(cubeVAO, lightingShader, model, 0.2784, 0.1843, 0.0901);

    //parallel uporer paya

    // Modelling Transformation
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 - 2.0f, 0.5f - 0.15f, translate_Z + 2.5f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.25f, 0.25f));
    model = alTogether * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //lightingShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    drawCube(cubeVAO, lightingShader, model, 0.2784, 0.1843, 0.0901);


    //chair done

}

void table(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    //table start ,pataton

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.25 - 2.0f, 0.3f - 0.25f, 0.8f + 2.5f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.25f, 1.2f));
    model = alTogether * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //lightingShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    drawCube(cubeVAO, lightingShader, model, 0.3176, 0.2117, 0.1019);

    //table pataton er uporer part


    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.25 - 2.0f, 0.448f - 0.25f, 0.8f + 2.5f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, -0.05f, 1.2f));
    model = alTogether * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //lightingShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);


    //table paya back right

    // Modelling Transformation
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.25 - 2.0f, -0.5f, 0.8f + 2.5f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 1.1f, 0.25f));
    model = alTogether * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //lightingShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    drawCube(cubeVAO, lightingShader, model, 0.3176, 0.2117, 0.1019);

    //table paya front right

    // Modelling Transformation
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.25 - 2.0f, -0.5f, 1.275f + 2.5f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 1.1f, 0.25f));
    model = alTogether * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //lightingShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    drawCube(cubeVAO, lightingShader, model, 0.3176, 0.2117, 0.1019);


    //table paya back left

    // Modelling Transformation
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.625 - 2.0f, -0.5f, 0.8f + 2.5f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 1.1f, 0.25f));
    model = alTogether * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //lightingShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    drawCube(cubeVAO, lightingShader, model, 0.3176, 0.2117, 0.1019);



    //table paya front left


    // Modelling Transformation
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.625 - 2.0f, -0.5f, 1.275f + 2.5f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 1.1f, 0.25f));
    model = alTogether * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //lightingShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    drawCube(cubeVAO, lightingShader, model, 0.3176, 0.2117, 0.1019);


    //table done

}

void longtable(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    //table start ,pataton

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.25 - 2.0f, 0.3f - 0.25f, 0.8f + 2.5f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 0.25f, 3.0f));
    model = alTogether * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //lightingShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    drawCube(cubeVAO, lightingShader, model, 0.2784, 0.1843, 0.0901);

    //table pataton er uporer part

}

void floor(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.0f, -0.55f, -1.5f + 0.3f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(15.5f, 0.1f, 15.5f));
    model = alTogether * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //lightingShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    drawCube(cubeVAO, lightingShader, model, 0.2815f, 0.1337f, 0.1415f);
}

void wall1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, translate2Matrix;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.0f, -0.55f, -1.5f + 0.3f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(12.2f, 0.1f, 15.5f));
    translate2Matrix = glm::translate(identityMatrix, glm::vec3(7.75f, 0.0f, 0.0f));
    model = alTogether * translate2Matrix * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //lightingShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    drawCube(cubeVAO, lightingShader, model, 0.6f, 0.5372f, 0.4392f);
}

void wall2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.0f, -0.55f, -1.5f + 0.3f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(15.5f, 0.1f, 12.2f));
    model = alTogether * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //lightingShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    drawCube(cubeVAO, lightingShader, model, 0.2823f, 0.4705f, 0.6667f);
}

void table2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{

       const int numCubes = 3480;
        const float xradius = 0.2f; // Radius glass
        const float zradius = 0.1f;
        const float angleIncrement = 0.1034f;
        glm::mat4 model, rotateXMatrix, rotateYMatrix, rotateZMatrix;

        lightingShader.use();

        for (int i = 0; i < numCubes; ++i)
        {

            float angle = glm::radians(i * angleIncrement);
            float xPosRed = xradius * cos(angle) + 0.5 * 6.0f;
            float zPosRed = zradius * sin(angle) + 0.5 * 7.0f;


            
            glm::mat4 ModelMatrix = glm::mat4(1.0f);
            ModelMatrix = glm::translate(ModelMatrix, glm::vec3(xPosRed,0.5 * 1.7f,zPosRed));
            ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2.0f, 0.1f, 2.0f));
            ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            ModelMatrix = glm::rotate(ModelMatrix, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));


            glm::vec3 cubeColor = glm::vec3(0.835f, 0.886f, 0.922f); // glass

            lightingShader.setVec3("cubeColor", cubeColor);



            float r = 0.835f;
            float g = 0.886f;
            float b = 0.922f;

            lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
            lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
            lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
            lightingShader.setVec3("material.emmisive", glm::vec3(r * 0.1, g * 0.1, b * 0.0));
            lightingShader.setFloat("material.shininess", 32.0f);

            ModelMatrix = alTogether * ModelMatrix;


            lightingShader.setMat4("model", ModelMatrix);

            glBindVertexArray(cubeVAO);
        
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
           




        }
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);


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

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 0.1;
        else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
        else rotateAngle_Z -= 0.1;
    }

   
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) 
    { 
        if (directionallighton) { directionallighton = false; }
        else { directionallighton = true; }
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
    {
        {
            if (spotlight1on) { spotlight1on = false; }
            else { spotlight1on = true; }
        }
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
    {

        {
            if (spotlight2on) { spotlight2on = false; }
            else { spotlight2on = true; }
        }
    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
    {

        {
            if (spotlight3on) { spotlight3on = false; }
            else { spotlight3on = true; }
        }
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
    {

        {
            if (spotlight4on) { spotlight4on = false; }
            else { spotlight4on = true; }
        }
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        rotateAngle_X += 0.1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        rotateAngle_Y += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotateAngle_Z += 0.1;
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

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_7 && action == GLFW_PRESS)
    {
        if (pointlight1on==true)
        {
            pointlight1on = false;
        }
        else
        {
            pointlight1on = true;
        }
    }


    else if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
    {
        if (pointlight2on == true)
        {
            pointlight2on = false;
        }
        else
        {
            pointlight2on = true;
        }
    }

    else if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
    {
        if (diffuseToggle)
        {

            pointlight1.turnDiffuseOff();
            pointlight2.turnDiffuseOff();
            pointlight3.turnDiffuseOff();
            pointlight4.turnDiffuseOff();
            diffuseToggle = !diffuseToggle;
        }
        else
        {

            pointlight1.turnDiffuseOn();
            pointlight2.turnDiffuseOn();
            pointlight3.turnDiffuseOn();
            pointlight4.turnDiffuseOn();
            diffuseToggle = !diffuseToggle;
        }
    }

    else if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {
        if (ambientToggle)
        {

            pointlight1.turnAmbientOff();
            pointlight2.turnAmbientOff();
            pointlight3.turnAmbientOff();
            pointlight4.turnAmbientOff();
            ambientToggle = !ambientToggle;
        }
        else
        {

            pointlight1.turnAmbientOn();
            pointlight2.turnAmbientOn();
            pointlight3.turnAmbientOn();
            pointlight4.turnAmbientOn();
            ambientToggle = !ambientToggle;
        }
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
