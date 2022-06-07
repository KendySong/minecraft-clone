#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Texture.h"

int main()
{
	int width = 1280;
	int height = 720;
	GLuint vao = 0;
	GLuint vbo = 0;
	GLuint ebo = 0;
	GLFWwindow* window;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, "Texture", NULL, NULL);
	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, width, height);
	glClearColor(0, 0, 0, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	float vertex[]
	{
		 0.5,  0.5, 0.0,	1, 1,
		 0.5, -0.5, 0.0,	1, 0,
		-0.5, -0.5, 0.0,	0, 0,
		-0.5,  0.5, 0.0,	0, 1
	};

	unsigned int indexBuffer[]
	{
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), &vertex, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexBuffer), &indexBuffer, GL_STATIC_DRAW);

	Shader shader("shaders/cube.vert", "shaders/cube.frag");
	glUseProgram(shader.GetProgram());
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Texture brickTex("textures/wall.jpg");
	Texture crateTex("textures/crate.png");

	int samplerLocation = 0;
	samplerLocation = glGetUniformLocation(shader.GetProgram(), "sampler");

	int brickTexSlot = 0;
	int crateTexSlot = 1;

	//Bind wall into slot 0
	glActiveTexture(GL_TEXTURE0 + brickTexSlot);
	glBindTexture(GL_TEXTURE_2D, brickTex.textureID);
	glUniform1i(samplerLocation, brickTexSlot);


	glActiveTexture(GL_TEXTURE0 + crateTexSlot);
	glBindTexture(GL_TEXTURE_2D, crateTex.textureID);
	


	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
	}
	return 0;
}