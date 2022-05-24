#include "Render.h"

Render::Render() 
{

}

void Render::Load(GLFWwindow* window, glm::vec2 windowSize) 
{
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, windowSize.x, windowSize.y);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glClearColor(0, 0.41, 0.29, 1);

	//Load shader
	Shader shader("shaders/cube.vert", "shaders/cube.frag");
	shader.Use();

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

	unsigned int ebo = 0;
	unsigned int vbo = 0;
	unsigned int vao = 0;

	camera = new Camera(window, windowSize.x, windowSize.y, 90, 0.1f, 100.0f, 0.4f, 0.01f, glm::vec3(0, 0, 0));

	camera->viewLocation = glGetUniformLocation(shader.GetProgramShader(), "view");
	glUniformMatrix4fv(camera->viewLocation, 1, false, glm::value_ptr(camera->view));
	camera->projectionLocation = glGetUniformLocation(shader.GetProgramShader(), "projection");
	glUniformMatrix4fv(camera->projectionLocation, 1, false, glm::value_ptr(camera->projection));
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0, 2.0f));

	int modelLoc = glGetUniformLocation(shader.GetProgramShader(), "model");
	glUniformMatrix4fv(modelLoc, 1, false, glm::value_ptr(model));
}

void Render::RenderFrame() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}