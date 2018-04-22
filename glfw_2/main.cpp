#include<iostream>
#include<GLFW\glfw3.h>
#include<glad\glad.h>



using namespace std;


void framebufferSizeCallback(GLFWwindow * mainWindow, int width, int height);
void getInput(GLFWwindow *window);

const char* vertex_shader_source = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main(){\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragment_shader_source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
"FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
"}\n\0";


int win_width = 800;
int win_height = 600;

int main() {

	float triangle_vertices[] = { -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f };


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* mainWindow = glfwCreateWindow(win_width, win_height, "Learning Triangle", NULL, NULL);
	if (mainWindow == NULL) { cout << "Window cannot be load" << endl; }
	glfwMakeContextCurrent(mainWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to load GLAD" << endl;
		return -1;
	}

	glViewport(0, 0, win_width, win_height);
	glfwSetFramebufferSizeCallback(mainWindow, framebufferSizeCallback);


	// Vertex buffer object
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

	// Vertex shader
	unsigned int vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	// Check compilation
	int success;
	char infolog[255];
	glad_glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(vertex_shader, 512, NULL, infolog);
	if(!success){
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << endl;
	}

	// Fragment shader
	unsigned int fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	// Check compilation
	glad_glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(fragment_shader, 512, NULL, infolog);
	if (!success) {
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << endl;
	}
	
	// Shader program


	


	//Render loop
	while (!glfwWindowShouldClose(mainWindow)) {
		getInput(mainWindow);
		glClearColor(1.f, 0.f, 0.f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}

void framebufferSizeCallback(GLFWwindow * mainWindow, int width, int height) {
	glViewport(0, 0, win_width, win_height);
}

void getInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}