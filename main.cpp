#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Current color
int currentColor = 0;

// Key callback function
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        currentColor = (currentColor + 1) % 3;
}

int main() {
    // Initialize the library
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Set key callback
    glfwSetKeyCallback(window, key_callback);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
        return -1;

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Set the clear color based on the current color
        if (currentColor == 0)
            glClearColor(0.5f, 0.0f, 0.5f, 1.0f); // Purple
        else if (currentColor == 1)
            glClearColor(1.0f, 0.5f, 0.0f, 1.0f); // Orange
        else
            glClearColor(0.0f, 1.0f, 1.0f, 1.0f); // Cyan

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}