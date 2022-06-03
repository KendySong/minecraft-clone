#include <vector>
#include <glm/glm.hpp>


#include "Shader.h"
#include <GLFW/glfw3.h>


float* rectVertPosition(glm::vec2 position) 
{
	float recVert[]
	{
		//Front face
		position.x - 0.5, position.y - 0.5,  0.0,
		position.x + 0.5, position.y - 0.5,  0.0,
		position.x + 0.5, position.y + 0.5,  0.0,
		position.x + 0.5, position.y + 0.5,  0.0,
		position.x - 0.5, position.y + 0.5,  0.0,
		position.x - 0.5, position.y - 0.5,  0.0
	};
	return recVert;
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Batch render", NULL, NULL);
	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, 1280, 720);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0, 0, 0, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	Shader shader("shaders/cube.vert", "shaders/cube.frag");
	glUseProgram(shader.CreateProgram());




	glm::vec2 position(-0.5f, 0.5f);
	float recVert[]
	{
		//Front face
		position.x - 0.5, position.y - 0.5,  0.0,
		position.x + 0.5, position.y - 0.5,  0.0,
		position.x + 0.5, position.y + 0.5,  0.0,
		position.x + 0.5, position.y + 0.5,  0.0,
		position.x - 0.5, position.y + 0.5,  0.0,
		position.x - 0.5, position.y - 0.5,  0.0
	};

	position.x = 0.5f;
	position.y = -0.5f;

	float recVert2[]
	{
		//Front face
		position.x - 0.5, position.y - 0.5,  0.0,
		position.x + 0.5, position.y - 0.5,  0.0,
		position.x + 0.5, position.y + 0.5,  0.0,
		position.x + 0.5, position.y + 0.5,  0.0,
		position.x - 0.5, position.y + 0.5,  0.0,
		position.x - 0.5, position.y - 0.5,  0.0
	};
	
	std::vector<float> vertex;
	vertex.insert(vertex.end(), &recVert[0], &recVert[std::size(recVert)]);
	vertex.insert(vertex.end(), &recVert2[0], &recVert2[std::size(recVert2)]);

	for (size_t i = 0; i < vertex.size(); i++)
	{
		std::cout << vertex[i] << "\n";
	}

	unsigned int vao = 0;
	unsigned int vbo = 0;
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), &vertex.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 12);
		glfwSwapBuffers(window);
	}
	return 0;
}