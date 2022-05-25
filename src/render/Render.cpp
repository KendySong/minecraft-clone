#include "Render.h"

Render::Render() 
{
	
}

void Render::Load(GLFWwindow* window, glm::vec2 windowSize) 
{
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, windowSize.x, windowSize.y);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0, 0.41, 0.29, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Load shader
	Shader shader("shaders/cube.vert", "shaders/cube.frag");
	shader.Use();

	//Instanciate camera
	camera = new Camera(window, windowSize.x, windowSize.y, 90, 0.1f, 100.0f, 0.4f, 5.0f, glm::vec3(0, 0, 0));
	camera->viewLocation = glGetUniformLocation(shader.GetProgramShader(), "view");
	glUniformMatrix4fv(camera->viewLocation, 1, false, glm::value_ptr(camera->view));
	camera->projectionLocation = glGetUniformLocation(shader.GetProgramShader(), "projection");
	glUniformMatrix4fv(camera->projectionLocation, 1, false, glm::value_ptr(camera->projection));

	//Set cube vertices and vao/vbo 
	float vertices[]
	{
		//Back face
		-0.5, -0.5, -0.5, 
		 0.5,  0.5, -0.5, 
		 0.5, -0.5, -0.5,    
		 0.5,  0.5, -0.5,  
		-0.5, -0.5, -0.5,  
		-0.5,  0.5, -0.5,  

		//Front face
		-0.5, -0.5,  0.5,  
		 0.5, -0.5,  0.5,    
		 0.5,  0.5,  0.5,   
		 0.5,  0.5,  0.5,   
		-0.5,  0.5,  0.5,  
		-0.5, -0.5,  0.5,  

		//Left face
		-0.5,  0.5,  0.5, 
		-0.5,  0.5, -0.5, 
		-0.5, -0.5, -0.5, 
		-0.5, -0.5, -0.5, 
		-0.5, -0.5,  0.5, 
		-0.5,  0.5,  0.5, 

		//Right face
		 0.5,  0.5,  0.5, 
		 0.5, -0.5, -0.5, 
		 0.5,  0.5, -0.5, 
		 0.5, -0.5, -0.5, 
		 0.5,  0.5,  0.5, 
		 0.5, -0.5,  0.5, 

		 //Bottom face
		 -0.5, -0.5, -0.5,  
		  0.5, -0.5, -0.5,  
		  0.5, -0.5,  0.5,  
		  0.5, -0.5,  0.5, 
		 -0.5, -0.5,  0.5, 
		 -0.5, -0.5, -0.5,  

		 //Top face
		 -0.5,  0.5, -0.5,  
		  0.5,  0.5,  0.5, 
		  0.5,  0.5, -0.5,  
		  0.5,  0.5,  0.5, 
		 -0.5,  0.5, -0.5,  
		 -0.5,  0.5,  0.5
	};

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

	//Create plane
	int positionsIndex = 0;
	glm::vec3 positions[100];
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			positions[positionsIndex] = glm::vec3(x, 0, y);
			positionsIndex++;
		}
	}

	//Set position of cubes into shaders
	for (int i = 0; i < 100; i++)
	{
		std::string positionName = "positions[" + std::to_string(i) + "]";
		int instanceLocation = glGetUniformLocation(shader.GetProgramShader(), positionName.c_str());
		glUniform3fv(instanceLocation, 1, glm::value_ptr(positions[i]));
	}
}

void Render::RenderFrame() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 100);
}