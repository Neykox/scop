#include "../include/scop.hpp"

// // Current color
// int currentColor = 0;

// // Key callback function
// void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
// {
// 	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
// 		glfwSetWindowShouldClose(window, GLFW_TRUE);
// 	if (key == GLFW_KEY_W && action == GLFW_PRESS)
// 		currentColor = (currentColor + 1) % 3;
// }

// int main() {
// 	// Initialize GLFW
// 	if (!glfwInit()) {
// 		return -1;
// 	}

// 	// Create a windowed mode window and its OpenGL context
// 	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
// 	if (!window) {
// 		glfwTerminate();
// 		return -1;
// 	}

// 	// Make the window's context current
// 	glfwMakeContextCurrent(window);

// 	// Set key callback
// 	glfwSetKeyCallback(window, key_callback);

// 	// Load OpenGL functions using GLAD
// 	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
// 		return -1;
// 	}

// 	// Loop until the user closes the window
// 	while (!glfwWindowShouldClose(window)) {
// 		// Render here
// 		// Set the clear color based on the current color
// 		if (currentColor == 0)
// 			glClearColor(0.5f, 0.0f, 0.5f, 1.0f); // Purple
// 		else if (currentColor == 1)
// 			glClearColor(1.0f, 0.5f, 0.0f, 1.0f); // Orange
// 		else
// 			glClearColor(0.0f, 1.0f, 1.0f, 1.0f); // Cyan

// 		glClear(GL_COLOR_BUFFER_BIT);

// 		// Swap front and back buffers
// 		glfwSwapBuffers(window);

// 		// Poll for and process events
// 		glfwPollEvents();
// 	}

// 	glfwTerminate();
// 	return 0;
// }

int main(int argc, char **argv)
{
	std::vector<Vec> vec;
	// int i = 0;

	// Check if a filename was provided
    if (argc < 2) {
        std::cerr << "Please provide a filename as an argument.\n";
        return 1;
    }

    // Open the file
    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

   // Read the file line by line
std::string line;
while (std::getline(file, line)) {
    // Check if the line starts with 'v'
    if (line.substr(0, 2) == "v ") {
        // Parse the line into x, y, z
        char* lineCStr = new char[line.length() + 1];
        std::strcpy(lineCStr, line.c_str());
        char* token = std::strtok(lineCStr, " ");
        if (token == nullptr) {
            std::cerr << "Failed to parse line: " << line << '\n';
            delete[] lineCStr;
            continue;
        }
        token = std::strtok(nullptr, " ");
        float x = std::stof(token ? token : "0");
        token = std::strtok(nullptr, " ");
        float y = std::stof(token ? token : "0");
        token = std::strtok(nullptr, " ");
        float z = std::stof(token ? token : "0");

        // Add the vertex to the vector
        vec.push_back(Vec(x, y, z));
        delete[] lineCStr;
    }
}

	std::cout << "Read " << vec.size() << " vertices.\n";
	std::cout << "vec.size = " << vec.size() << '\n';
	for (int i = 0; i < vec.size(); i++)
    	std::cout << vec[i] << '\n';
    return 0;
}