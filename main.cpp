#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
        return -1;

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Get the current time
        double time = glfwGetTime();

        // Calculate color components based on time
        float red = (sin(time) * 0.5f) + 0.5f;
        float green = (cos(time) * 0.5f) + 0.5f;
        float blue = (sin(time + 3.14159 / 2) * 0.5f) + 0.5f;

        // Set the clear color and clear the screen
        glClearColor(red, green, blue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
