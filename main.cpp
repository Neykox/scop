#include <SDL2/SDL.h>
#include <GLFW/glfw3.h>

// Current color
int currentColor = 0;

// Key callback function
void handle_key(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                SDL_Quit();
                exit(0);
            case SDLK_w:
                currentColor = (currentColor + 1) % 3;
        }
    }
}

int main() {
    // Initialize the library
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Create a windowed mode window and its OpenGL context
    SDL_Window* window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
    if (!window) {
        SDL_Log("Could not create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Make the window's context current
    SDL_GLContext context = SDL_GL_CreateContext(window);

    // Loop until the user closes the window
    SDL_Event event;
    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_Quit();
                return 0;
            }
            handle_key(event);
        }

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
        SDL_GL_SwapWindow(window);
    }

    SDL_Quit();
    return 0;
}