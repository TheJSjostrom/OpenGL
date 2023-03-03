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
		m_Shader2("res/shaders/Basic.shader2")
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

		// Pyramid vertex data
		float vertices3[] = {
		 // POSITION  ------- COLOR
		   -0.5f, 0.0f,-0.5f, 1.0f, 0.0f, 0.0f,
		   -0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f,
			0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f,
			0.5f, 0.0f,-0.5f, 1.0f, 0.0f, 0.0f,
		   -0.5f, 0.0f,-0.5f, 1.0f, 0.0f, 0.0f,
		    0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f,

		   -0.5f, 0.0f,-0.5f, 0.0f, 1.0f, 0.0f,
		   -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		    0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		   -0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
		   -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		    0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		   -0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

			0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f,
			0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.0F,-0.5f, 1.0f, 0.0f, 0.0f,
			0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

			0.5f, 0.0f,-0.5f, 1.0f, 1.0f, 0.0f,
			0.0f, 0.0f,-0.5f, 1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		   -0.5f, 0.0f,-0.5f, 1.0f, 1.0f, 0.0f,
			0.0f, 0.0f,-0.5f, 1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		};

		float vertices4[] = {
			0.0f, 0.5f, 0.0f, 0.5f, 1.0f,
		   -0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
		    0.5f,-0.5f, 0.0f, 1.0f, 0.0f
		};

		float vertices5[] = {
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

		// Create Vertex Buffer Objects & Vertex Array Object
		GLCall(glGenVertexArrays(5, m_VAO));	
		GLCall(glGenBuffers(5, m_Buffer));


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
		

		// Pyramid Vertex Data----------------------------------------------------------------------------------
		GLCall(glBindVertexArray(m_VAO[2]));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Buffer[2]));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW));
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0)); // Vertex Position
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)))); // Texture Coordinate
		GLCall(glEnableVertexAttribArray(1));
		// ------------------------------------------------------------------------------------------------------


		// triangle Vertex Data----------------------------------------------------------------------------------
		GLCall(glBindVertexArray(m_VAO[3]));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Buffer[3]));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4), vertices4, GL_STATIC_DRAW));
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0)); // Vertex Position
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)))); // Texture Coordinate
		GLCall(glEnableVertexAttribArray(1));
		// --------------------------------------------------------------------------------------------------------
		
		// triangle Vertex Data----------------------------------------------------------------------------------
		GLCall(glBindVertexArray(m_VAO[4]));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Buffer[4]));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices5), vertices5, GL_STATIC_DRAW));
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0)); // Vertex Position
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)))); // Texture Coordinate
		GLCall(glEnableVertexAttribArray(1));
		// --------------------------------------------------------------------------------------------------------

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
	
		glEnable(GL_DEPTH_TEST); 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		// Camera movement settings
		const float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		view = glm::lookAt(glm::vec3(camX, 3.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		//view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		//view = glm::translate(view, glm::vec3(0.0f,  0.0f, -15.0f)); // Camera position
		//view = glm::rotate(view, glm::radians(32.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		// -------------------------------------------------------------------------------------------
	   
		// Projection Matrix
		proj = glm::perspective(glm::radians(45.0f), (float)960 / (float)540, 0.1f, 100.0f);
		
		if (m_XValue >= 1) {
			m_Switch = 0;
		}
		else if (m_XValue <= -1) {
			m_Switch = 1;
		}

		if (m_Switch == 1) {
			m_XValue += 0.01f;
		}
		else if (m_Switch == 0) {
			m_XValue -= 0.01f;
		}
		
		float z = m_x * m_x;
		
		if (m_x >= 3) {
			m_Switch2 = 0;
		}
		else if (m_x <= -3) {
			m_Switch2 = 1;
			}

		if (m_Switch2 == 1) {
			m_x += 0.05f;
		}
		else if (m_Switch2 == 0) {
			m_x -= 0.05f;
		}

		const float cameraSpeed = 0.05f; // adjust accordingly
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;


		// Draw boxes -------------------------------------
		const glm::vec3 boxPos[] = {
			glm::vec3(m_x, 0.5f, z),
			glm::vec3(-2.0f, 0.5f, 0.0f),
			glm::vec3(-2.0f, 0.5f,-2.0f),
			glm::vec3(0.0f, 0.5f,-2.0f),
			glm::vec3(2.0f, 0.5f, 0.0f),
			glm::vec3(2.0f, 0.5f,-2.0f),
			glm::vec3(0.0f, 0.5f,-4.0f),
			glm::vec3(-2.0f, 0.5f,-4.0f),
			glm::vec3(2.0f, 0.5f,-4.0f),
			glm::vec3(-4.5f, 0.5f, 4.5f),
			glm::vec3(-4.5f, 1.5f, 4.5f),
			glm::vec3(-3.5f, 0.5f, 4.5f),
			glm::vec3(-4.5f, 0.5f, 3.5f)
		};

		m_Shader.Bind();
		GLCall(glBindVertexArray(m_VAO[0]));
		glBindTexture(GL_TEXTURE_2D, m_texture);

		for (int i = 0; i < 13; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, boxPos[i]);
			glm::mat4 mvp = proj * view * model;
			m_Shader.SetUniformMat4f("u_MVP", mvp);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		}
		// -------------------------------------------------
		 

		//Draw floor ----------------------------------------
		m_Shader.Bind();
		GLCall(glBindVertexArray(m_VAO[1]));
		glBindTexture(GL_TEXTURE_2D, m_texture2);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.25f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 0.5f, 10.0f));
		glm::mat4 mvp = proj * view * model;
		m_Shader.SetUniformMat4f("u_MVP", mvp);
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		// -----------------------------------------------------

		// Draw wall -------------------------------------------
		m_Shader.Bind();
		GLCall(glBindVertexArray(m_VAO[4]));
		glBindTexture(GL_TEXTURE_2D, m_texture4);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.25f, 5.25f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 0.5f, 10.0f));
		mvp = proj * view * model;
		m_Shader.SetUniformMat4f("u_MVP", mvp);
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		// -----------------------------------------------------
		
		
		// Draw pyramid -----------------------------------------
		m_Shader2.Bind();
		GLCall(glBindVertexArray(m_VAO[2]));
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 2.0f));
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		mvp = proj * view * model;
		m_Shader2.SetUniformMat4f("u_MVP", mvp);
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 30));
		// -------------------------------------------------------


		// Draw Triangle -----------------------------------------
		const glm::vec3 TriPos[] = {
			glm::vec3(0.0f, 3.0f, 4.0f),
			glm::vec3(0.5f, 2.0f, 4.0f),
			glm::vec3(-0.5f, 2.0f, 4.0f)
		};

		m_Shader.Bind();
		glBindTexture(GL_TEXTURE_2D, m_texture3);
		GLCall(glBindVertexArray(m_VAO[3]));

		for (int i = 0; i < 3; i++) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, TriPos[i]);
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			mvp = proj * view * model;
			m_Shader.SetUniformMat4f("u_MVP", mvp);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
		}
		// --------------------------------------------------------------
	}

	void TestTexture2D::OnImGuiRender()
	{	
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
	
}
