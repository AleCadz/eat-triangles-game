#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <random>

void error_callback(int error, const char *description);
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void draw_square(float x, float y);
void draw_triangle();

float square_x = 0.0f;
float square_y = 0.0f;
float triangle_x = 0.5f;
float triangle_y = 0.5f;
float squareYModifier = 0.05f;
float squareXModifier = 0.05f;
std::random_device rd;  
std::mt19937 gen(rd()); 
std::uniform_real_distribution<float> dist(-0.80f, 0.80f);
float random_number = dist(gen);

int main()
{
    if (!glfwInit())
    {
        error_callback(400, "Error inicializando glfw");
        glfwTerminate();
        return -1;
    }
    GLFWwindow *window = glfwCreateWindow(1200, 1000, "Move the square with the arrow keys", NULL, NULL);
    if (!window)
    {
        error_callback(400, "Error creando ventana");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    GLenum err = glewInit();

    if (err != GLEW_OK)
    {
        fprintf(stderr, "Error inicializando GLEW: %s\n", glewGetErrorString(err));
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        draw_triangle();
        draw_square(square_x, square_y);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    const float move_amount = 0.05f;

    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
        case GLFW_KEY_UP:
            square_y += move_amount;
            break;
        case GLFW_KEY_DOWN:
            square_y -= move_amount;
            break;
        case GLFW_KEY_LEFT:
            square_x -= move_amount;
            break;
        case GLFW_KEY_RIGHT:
            square_x += move_amount;
            break;
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        }
    }
}

void draw_square(float x, float y)
{
    glBegin(GL_QUADS);
    glColor3f(0.98f, 0.625f, 0.12f);

    glVertex2f(x - squareXModifier, y - squareYModifier);
    glVertex2f(x + squareXModifier, y - squareYModifier);
    glVertex2f(x + squareXModifier, y + squareYModifier);
    glVertex2f(x - squareXModifier, y + squareYModifier);

    glEnd();
}

void draw_triangle()
{
    glBegin(GL_TRIANGLES);
    glColor3f(0.50f, 0.50f, 0.50f);
    glVertex3f(-0.05f+random_number, -0.05f+random_number, 0.0f+random_number);
    glVertex3f(0.05f+random_number, -0.05f+random_number, 0.0f+random_number);
    glVertex3f(0.0f+random_number, 0.05f+random_number, 0.0f+random_number);
    glEnd();
}
