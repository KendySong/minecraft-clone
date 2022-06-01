#include "Render.h"

Render::Render() 
{
	
}

void Render::Load(GLFWwindow* window, glm::vec2 windowSize) 
{
	//Set cube vertices
	float vertices[]
	{
		//Front face
		-0.5, -0.5,  0.5,
		0.5, -0.5,  0.5,
		0.5,  0.5,  0.5,
		0.5,  0.5,  0.5,
		-0.5,  0.5,  0.5,
		-0.5, -0.5,  0.5,

		//Back face
		-0.5, -0.5, -0.5,
		0.5,  0.5, -0.5,
		0.5, -0.5, -0.5,
		0.5,  0.5, -0.5,
		-0.5, -0.5, -0.5,
		-0.5,  0.5, -0.5,

		//Right face
		0.5,  0.5,  0.5,
		0.5, -0.5, -0.5,
		0.5,  0.5, -0.5,
		0.5, -0.5, -0.5,
		0.5,  0.5,  0.5,
		0.5, -0.5,  0.5,

		//Left face
		-0.5,  0.5,  0.5,
		-0.5,  0.5, -0.5,
		-0.5, -0.5, -0.5,
		-0.5, -0.5, -0.5,
		-0.5, -0.5,  0.5,
		-0.5,  0.5,  0.5,

		//Top face
		-0.5,  0.5, -0.5,
		0.5,  0.5,  0.5,
		0.5,  0.5, -0.5,
		0.5,  0.5,  0.5,
		-0.5,  0.5, -0.5,
		-0.5,  0.5,  0.5,

		//Bottom face
		-0.5, -0.5, -0.5,
		0.5, -0.5, -0.5,
		0.5, -0.5,  0.5,
		0.5, -0.5,  0.5,
		-0.5, -0.5,  0.5,
		-0.5, -0.5, -0.5	
	};

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, windowSize.x, windowSize.y);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glClearColor(0, 0.41, 0.29, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Load shader
	Shader shader("shaders/cube.vert", "shaders/cube.frag");
	shader.Use();
	_locModel = glGetUniformLocation(shader.GetProgramShader(), "model");

	//Instanciate camera
	camera = new Camera(window, windowSize.x, windowSize.y, 90, 0.1f, 100.0f, 0.4f, 5.0f, glm::vec3(0, 0, 0));
	camera->viewLocation = glGetUniformLocation(shader.GetProgramShader(), "view");
	glUniformMatrix4fv(camera->viewLocation, 1, false, glm::value_ptr(camera->view));
	camera->projectionLocation = glGetUniformLocation(shader.GetProgramShader(), "projection");
	glUniformMatrix4fv(camera->projectionLocation, 1, false, glm::value_ptr(camera->projection));

	//VAO/VBO/Configure shaders
	unsigned int vbo = 0;
	unsigned int vao = 0;
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Render::RenderFrame() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (size_t i = 0; i < _world.displayChunks.size(); i++)
	{
		for (size_t j = 0; j < _world.displayChunks[i].blocks.size(); j++)
		{
			glm::mat4 currentPosition(1.0f);
			currentPosition = glm::translate(currentPosition, _world.displayChunks[i].blocks[j].pos);
			glUniformMatrix4fv(_locModel, 1, false, glm::value_ptr(currentPosition));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
	
	//0- 6	FRONT
	//6- 6	BACK
	//12-6	RIGHT
	//18-6	LEFT
	//26-6	TOP
	//30-6	BOT
}