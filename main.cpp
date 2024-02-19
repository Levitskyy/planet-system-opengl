#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cstdio>
#include "Camera.h"
#include "Sphere.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Камера
Camera camera(glm::vec3(0.0f, 0.0f, 30.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

bool firstMouse = true;

// Тайминги
float deltaTime = 0.0f;	// время между текущим кадром и последним кадром
float lastFrame = 0.0f;

glm::vec3 lightPos(0.0f, 0.0f, 0.0f);


struct Planet {
    glm::vec3 color;
    glm::vec3 size;
    glm::vec3 pos;
    float speed;
    float radius = 0;
    Planet *satellite = NULL;
};



int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Window", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW winow\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Сообщаем GLFW, чтобы он захватил наш курсор
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    Shader lamp("../Shaders/lamp.vs", "../Shaders/lamp.fs");
    Shader lighting("../Shaders/lighting.vs", "../Shaders/lighting.fs");

    Sphere sphere(1.0f, 48, 48, true);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    GLuint vboId;
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);           // for vertex data
    glBufferData(GL_ARRAY_BUFFER,                   // target
        sphere.getInterleavedVertexSize(), // data size, # of bytes
        sphere.getInterleavedVertices(),   // ptr to vertex data
        GL_STATIC_DRAW);                   // usage

    GLuint iboId;
    glGenBuffers(1, &iboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);   // for index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,           // target
        sphere.getIndexSize(),             // data size, # of bytes
        sphere.getIndices(),               // ptr to index data
        GL_STATIC_DRAW);                   // usage


    int stride = sphere.getInterleavedStride();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, stride, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnable(GL_DEPTH_TEST);

    Planet planets[4];
    planets[0] = Planet{
        glm::vec3(0.5f, 0.5f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        0.5f,
        15.0f
    };
    planets[1] = Planet{
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        0.6f,
        25.0f,
        &planets[3]
    };
    planets[2] = Planet{
        glm::vec3(0.0f, 0.5f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        0.3f,
        35.0f
    };
    planets[3] = Planet{
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(10.0f, 10.0f, 10.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        0.1f,
        100.0f
    };

    for (auto& planet : planets) {
        planet.pos = glm::vec3(planet.radius, 0.0f, 0.0f);
        if (planet.satellite != NULL) {
            if (planet.satellite->speed >= 0)
                planet.speed = -planet.speed;
        }
    }


    while (!glfwWindowShouldClose(window)) {

        // Логическая часть работы со временем для каждого кадра
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lamp.use();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));

        lamp.setMat4("projection", projection);
        lamp.setMat4("view", view);
        lamp.setMat4("model", model);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sphere.getIndexCount(), GL_UNSIGNED_INT, (void*)0);

        for (auto &planet : planets) {
            lighting.use();
            lighting.setVec3("objectColor", planet.color);
            lighting.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
            lighting.setVec3("lightPos", lightPos);
            lighting.setVec3("viewPos", camera.Position);
            
            // Преобразования Вида/Проекции
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
            glm::mat4 view = camera.GetViewMatrix();
            lighting.setMat4("projection", projection);
            lighting.setMat4("view", view);

            // Мировое преобразование
            glm::mat4 model = glm::mat4(1.0f);
            glm::vec3 planet_offset = glm::vec3(0.0f, 0.0f, 0.0f);
            if (planet.satellite != NULL) {
                planet_offset = planet.satellite->pos;
            }
            planet.pos = glm::vec3(sin(currentFrame * planet.speed) * planet.radius, planet.pos.y, cos(currentFrame * planet.speed) * planet.radius) + planet_offset;
            model = glm::translate(model, planet.pos);
            model = glm::scale(model, planet.size);
            lighting.setMat4("model", model);

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, sphere.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &vboId);

    glfwTerminate();
    return 0;
}


// Обработка всех событий ввода: запрос GLFW о нажатии/отпускании кнопки мыши в данном кадре и соответствующая обработка данных событий
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: всякий раз, когда изменяются размеры окна (пользователем или операционной системой), вызывается данная callback-функция
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Убеждаемся, что окно просмотра соответствует новым размерам окна.
    // Обратите внимание, ширина и высота будут значительно больше, чем указано, на Retina-дисплеях
    glViewport(0, 0, width, height);
}

// glfw: всякий раз, когда перемещается мышь, вызывается данная callback-функция
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // перевернуто, так как y-координаты идут снизу вверх

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: всякий раз, когда прокручивается колесико мыши, вызывается данная callback-функция
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

