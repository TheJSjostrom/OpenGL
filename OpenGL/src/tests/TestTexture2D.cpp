#include "TestTexture2D.h"

#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"

#include "stb_image/stb_image.h"

namespace test {

	TestTexture2D::TestTexture2D()
		: m_Shader("res/shaders/Basic.shader"),
		m_Shader2("res/shaders/Basic.shader2"),
		m_Shader3("res/shaders/Basic.shader3")
	{
		// Boxes vertex data
		float vertices[] = {
		   // POSITION   ------  TEXT. COORDINATE
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		// Floor vertex data
		float vertices2[] = {
		  // POSITION   ------   TEXT. COORDINATE
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};


		float vertices3[] = {
			// POSITION   ------   TEXT. COORDINATE
			  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			   0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			   0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			   0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			  -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			  -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			   0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			   0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			   0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			   0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			  -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		float vertices4[] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};

		// Create Vertex Buffer Objects & Vertex Array Object
		GLCall(glGenVertexArrays(4, m_VAO));	
		GLCall(glGenBuffers(4, m_Buffer));


		// Boxes Vertex Data ------------------------------------------------------------------------------------
		GLCall(glBindVertexArray(m_VAO[0]));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Buffer[0]));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0)); // Vertex Position
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)))); // Texture Coordinate
		GLCall(glEnableVertexAttribArray(1));
		// ------------------------------------------------------------------------------------------------------
		

		// floor Vertex Data-------------------------------------------------------------------------------------
		GLCall(glBindVertexArray(m_VAO[1]));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Buffer[1]));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW));
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0)); // Vertex Position
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)))); // Texture Coordinate
		GLCall(glEnableVertexAttribArray(1));
		// -----------------------------------------------------------------------------------------------------

		
		// Wall Vertex Data----------------------------------------------------------------------------------
		GLCall(glBindVertexArray(m_VAO[2]));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Buffer[2]));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW));
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0)); // Vertex Position
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)))); // Texture Coordinate
		GLCall(glEnableVertexAttribArray(1));
		// --------------------------------------------------------------------------------------------------------


		// Cube Vertex Data -------------------------------------------------------------------------------------------
		GLCall(glBindVertexArray(m_VAO[3]));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Buffer[3]));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4), vertices4, GL_STATIC_DRAW));
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0)); // Vertex Position
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)))); // Vertex Position
		GLCall(glEnableVertexAttribArray(1));
		// ------------------------------------------------------------------------------------------------------------
		 
		
		// Light Cube Vertex Data ------------------------------------------------------------------------------------
		GLCall(glBindVertexArray(m_VAO[4]));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Buffer[3]));
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0)); // Vertex Position
		GLCall(glEnableVertexAttribArray(0));
		// ------------------------------------------------------------------------------------------------------------

		// TEXTURES
		// Wooden texture -----------------------------------------------------------------------------------------
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load and generate the texture
		int width, height, nrChannels;
		unsigned char* data = stbi_load("res/textures/wooden.jpg", &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
		// -------------------------------------------------------------------------------------------------------
		

		// Grass texture -----------------------------------------------------------------------------------------
		glGenTextures(1, &m_texture2);
		glBindTexture(GL_TEXTURE_2D, m_texture2);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load and generate the texture
		data = stbi_load("res/textures/grass3.jpg", &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
		// ------------------------------------------------------------------------------------------------------
		

		// Wet metallic texture ----------------------------------------------------------------------------------
		glGenTextures(1, &m_texture3);
		glBindTexture(GL_TEXTURE_2D, m_texture3);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load and generate the texture
		data = stbi_load("res/textures/rusty.jpg", &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
		// ----------------------------------------------------------------------------------------------------
	
		glGenTextures(1, &m_texture4);
		glBindTexture(GL_TEXTURE_2D, m_texture4);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load and generate the texture
		data = stbi_load("res/textures/redbricks.jpg", &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
		// ----------------------------------------------------------------------------------------------------
	}

	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}

	void TestTexture2D::OnRender(GLFWwindow* window)
	{	
		
		// Clear color buffer -------------------------------
		glEnable(GL_DEPTH_TEST); 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// ----------------------------------------------------  

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		// Camera settings
		
		view = glm::lookAt(m_camPos, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0, 1.0, 0.0));
		//const float radius = 5.0f;
		//float camX = sin(glfwGetTime()) * radius;
		//float camZ = cos(glfwGetTime()) * radius;
		//view = glm::lookAt(glm::vec3(camX, 2.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		//view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		//view = glm::translate(view, glm::vec3(-4.0f, 0.0f, 0.0f)); // Camera position
		//view = glm::rotate(view, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		// -------------------------------------------------------------------------------------------
	   
		// Projection Matrix
		proj = glm::perspective(glm::radians(45.0f), (float)960 / (float)540, 0.1f, 100.0f);
		
		
		float zPos = m_x;

		if (m_x >= 2) {
			m_Switch = 0;
		}
		else if (m_x <= -2) {
			m_Switch = 1;
			}

		if (m_Switch == 1) {
			m_x += 0.05f;
		}
		else if (m_Switch == 0) {
			m_x -= 0.05f;
		}
 
		const float cameraSpeed = 0.05f; // adjust accordingly
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			m_lightPos.z -= 0.05;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			m_lightPos.z += 0.05;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			m_lightPos.x -= 0.05;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			m_lightPos.x += 0.05f;
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			m_camPos.y += 0.05f;
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			m_camPos.y -= 0.05f;
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
			m_camPos.x -= 0.05f;
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
			m_camPos.x += 0.05f;
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
			m_lightPos.y += 0.05f;
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
			m_lightPos.y -= 0.05f;

		// Draw boxes -------------------------------------
		const glm::vec3 boxPos[] = {
			glm::vec3(m_x, 0.0f, zPos),
			glm::vec3(-2.0f, 0.0f, 0.0f),
			glm::vec3(-2.0f, 0.0f,-2.0f),
			glm::vec3(0.0f, 0.0f,-2.0f),
			glm::vec3(2.0f, 0.0f, 0.0f),
			glm::vec3(2.0f, 0.0f,-2.0f),
			glm::vec3(0.0f, 0.0f,-4.0f),
			glm::vec3(-2.0f, 0.0f,-4.0f),
			glm::vec3(2.0f, 0.0f,-4.0f),
			glm::vec3(-4.5f, 0.0f, 4.5f),
			glm::vec3(-4.5f, 1.0f, 4.5f),
			glm::vec3(-3.5f, 0.0f, 4.5f),
			glm::vec3(-4.5f, 0.0f, 3.5f),
		 
		};

		m_Shader.Bind();
		GLCall(glBindVertexArray(m_VAO[0]));
		glBindTexture(GL_TEXTURE_2D, m_texture);

		for (int i = 0; i < 14; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, boxPos[i]);
			glm::mat4 mvp = proj * view * model;
			m_Shader.SetUniformMat4f("u_MVP", mvp);
			//GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		}
		// -------------------------------------------------
		 

		//Draw floor ----------------------------------------
		m_Shader.Bind();
		GLCall(glBindVertexArray(m_VAO[1]));
		glBindTexture(GL_TEXTURE_2D, m_texture2);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.75f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 0.5f, 10.0f));
		glm::mat4 mvp = proj * view * model;
		m_Shader.SetUniformMat4f("u_MVP", mvp);
		//GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		// -----------------------------------------------------


		// Draw wall -------------------------------------------
		m_Shader.Bind();
		GLCall(glBindVertexArray(m_VAO[2]));
		glBindTexture(GL_TEXTURE_2D, m_texture4);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.25f, 5.25f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 0.5f, 10.0f));
		mvp = proj * view * model;
		m_Shader.SetUniformMat4f("u_MVP", mvp);
	    //GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		// -----------------------------------------------------

		// Draw floor Cube -------------------------------------------
		m_Shader2.Bind();
		GLCall(glBindVertexArray(m_VAO[3]));
		m_Shader2.SetUniform3f("objectColor", m_ObjectColor.r, m_ObjectColor.g, m_ObjectColor.b);
		m_Shader2.SetUniform3f("lightColor", m_LightColor.r, m_LightColor.g, m_LightColor.b);
		m_Shader2.SetUniform3f("lightPos", m_lightPos.x, m_lightPos.y, m_lightPos.z);
		m_Shader2.SetUniform3f("viewPos", m_camPos.x, m_camPos.y, m_camPos.z);
		model = glm::mat4(1.0f);
		model = glm::translate(model, m_trans);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(m_rot), glm::vec3(1.0f, 0.5f, 0.0f));
		model = glm::scale(model, m_scale);
		m_Shader2.SetUniformMat4f("model", model);
		mvp = proj * view * model;
		m_Shader2.SetUniformMat4f("u_MVP", mvp);
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		// -----------------------------------------------------
		
		// Draw Light Cube ------------------------------------------
		const float radius = 5.0f;
		float camX = sin(m_LightObjPos) * radius;
		float camZ = cos(m_LightObjPos) * radius;
		m_lightPos.x = camX;
		m_lightPos.z = camZ;
		m_Shader3.Bind();
		GLCall(glBindVertexArray(m_VAO[4]));
		model = glm::mat4(1.0f);
		model = glm::translate(model, m_lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		mvp = proj * view * model;
		m_Shader3.SetUniformMat4f("u_MVP", mvp);
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		// --------------------------------------------------------

		// IMGUI
		//----------------------------------------------------------
		ImGui::Begin("Editor");
			// Lighting settings
			ImGui::Text("Light Settings");
			ImGui::ColorEdit3("Light color", &m_LightColor.r);
			ImGui::SliderFloat("Light Direction", &m_LightObjPos, 0.0f, 10.0f);
			ImGui::Text("");

			// Object Settings
			ImGui::Text("Object Settings");
			ImGui::ColorEdit3("Object color", &m_ObjectColor.r);
			ImGui::Text("");
			ImGui::Text("Transform");
			ImGui::SliderFloat3("Translation", &m_trans.x, -10.0f, 10.0f);
			ImGui::SliderFloat3("Scale", &m_scale.x, 0.0f, 10.0f);
			ImGui::SliderFloat("Rotation", &m_rot, 0.0f, 100.0f);

		ImGui::End();

		ImGui::ShowDemoWindow();
		//----------------------------------------------------------
	}

	void TestTexture2D::OnImGuiRender()
	{	
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
	
}
