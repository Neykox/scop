//##########################################################################################
//tuto with square

#include "../include/scop.hpp"
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>

// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// using namespace glm;

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec3 aColor;\n"
	"out vec3 ourColor;\n"
	"uniform mat4 MVP;\n"
	"void main()\n"
	"{\n"
	"   //gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"	//Output position of the vertex, in clip space : MVP * position\n"
	"	gl_Position =  MVP * vec4(aPos,1);\n"
	"	ourColor = aColor;\n"
	"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"in vec3 ourColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vec4(ourColor, 1.0f);\n"
	"}\n\0";

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
	std::string objName;
	while (std::getline(file, line)) {
		// Check if the line starts with 'o'
		if (line.substr(0, 2) == "o ")
			objName = line.substr(2);

		// Check if the line starts with 'v'
		if (line.substr(0, 2) == "v ") {
			// Parse the line into x, y, z
			char* lineCStr = new char[line.length() + 1];
			strcpy(lineCStr, line.c_str());
			char* token = strtok(lineCStr, " ");
			if (token == nullptr) {
				std::cerr << "Failed to parse line: " << line << '\n';
				delete[] lineCStr;
				continue;
			}
			token = strtok(nullptr, " ");
			float x = std::stof(token ? token : "0");
			token = strtok(nullptr, " ");
			float y = std::stof(token ? token : "0");
			token = strtok(nullptr, " ");
			float z = std::stof(token ? token : "0");

			// Add the vertex to the vector
			vec.push_back(Vec(x, y, z));
			delete[] lineCStr;
		}
	}

	for (Vec& v : vec)
	{
		std::cout << "b " << v << '\n';
		//dont know about that one chief
		//if (v.x > 1 || v.x < -1 || v.y > 1 || v.y < -1 || v.z > 1 || v.z < -1)
		if(v.x != 0 && v.y != 0 && v.z != 0)
			v.normalize();
		std::cout << "a " << v << "\n\n";
	}

	// std::cout << "Read " << vec.size() << " vertices.\n";
	// std::cout << "vec.size = " << vec.size() << '\n';
	// for (int i = 0; i < vec.size(); i++)
	// 	std::cout << vec[i] << '\n';

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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, objName.empty() ? "Namen't" : objName.c_str(), NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	// float vertices[] = {
	// 	0.5f, 0.5f, 0.0f, // left  
	// 	0.5f, -0.5f, 0.0f, // right 
	// 	-0.5f,  0.5f, 0.0f,  // top

	// 	 0.5f, -0.5f, 0.0f,
	// 	 -0.5f, -0.5f, 0.0f,
	// 	 -0.5f, 0.5f, 0.0f
	// }; 
	// float* vertices = new float[vec.size() * 3];  // Each Vec has 3 components

	// for (size_t i = 0; i < vec.size(); ++i) {
	// 	vertices[i * 3] = vec[i].x;
	// 	vertices[i * 3 + 1] = vec[i].y;
	// 	vertices[i * 3 + 2] = vec[i].z;
	// }

	float vertices[vec.size() * 6];
	for (int i = 0, v = 0, c = 0; i < vec.size() * 6; i = i + 6, v++)
	{
		vertices[i] = vec[v].x;
		vertices[i + 1] = vec[v].y;
		vertices[i + 2] = vec[v].z;
		if (c == 0)
		{
			vertices[i + 3] = 0.87;
			vertices[i + 4] = 0;
			vertices[i + 5] = 1;
			c++;
		}
		else if (c == 1)
		{
			vertices[i + 3] = 1;
			vertices[i + 4] = 1;
			vertices[i + 5] = 1;
			c++;
		}
		else
		{
			vertices[i + 3] = 0;
			vertices[i + 4] = 1;
			vertices[i + 5] = 1;
			c = 0;
		}

		//black and white
		// if (vec[v].z < 0)
		// {
		// 	vertices[i + 3] = 0;
		// 	vertices[i + 4] = 0;
		// 	vertices[i + 5] = 0;
		// }
		// else
		// {
		// 	vertices[i + 3] = 1;
		// 	vertices[i + 4] = 1;
		// 	vertices[i + 5] = 1;
		// }
	}

	std::cout << "vec.size() = " << vec.size() << " | vertices = \n";
	for (int i = 0; i < vec.size() * 6; i = i + 6)
	{
		std::cout << vertices[i] << " " << vertices[i + 1] << " " << vertices[i + 2] <<"\n";
	}

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// modified draw call
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, vec.size() * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0); 


	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	Mat4 Projection = Mat4::perspective(Mat4::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
	
	// Camera matrix
	Mat4 View       = Mat4::lookAt(
								Vec(4,3,3), // Camera is at (4,3,3), in World Space
								Vec(0,0,0), // and looks at the origin
								Vec(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );
	// Model matrix : an identity matrix (model will be at the origin)
	Mat4 Model      = Mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	Mat4 mvp        = Projection * View * Model; // Remember, matrix multiplication is the other way around


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw our first triangle
		glUseProgram(shaderProgram);

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, vec.size());// * 3);
		// glBindVertexArray(0); // no need to unbind it every time 
 
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	// delete[] vertices;
	file.close();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

