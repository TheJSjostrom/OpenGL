#include "TestTexture2D.h"

#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"

namespace test {

	TestTexture2D::TestTexture2D()
		: m_Shader("res/shaders/Basic.shader"),
		m_Shader2("res/shaders/Basic.shader2")
	{
		
 

		m_Shader.Bind();
 
		float vertices[] = {
			 
			// positions         // colors 
			// First triangle
			 0.0f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  
			-0.15f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,   
			 0.15f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,

			 // Second triangle
			-0.15f,0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
			-0.3f,-0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
			 0.0f,-0.5f, 0.0f,   0.0f, 0.0f, 1.0f,

			 // Third triangle
			 0.15f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
			 0.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
			 0.3f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
		};

		// Create Vertex Buffer Object and Vertex Array Object
		GLCall(glGenBuffers(3, m_Buffer));
		
		// First triangle setup
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Buffer[0]));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
		
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));
		GLCall(glEnableVertexAttribArray(1));
	}

	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}

	void TestTexture2D::OnRender(GLFWwindow* window)
	{	
	
		const float i = 0.005; // The value who changing m_XValue each frame.

		// Keep track of
		const float XCoord = -0.3; // Store the vertex position x coordinate (Second triangle's Second vertex)
		const float XCoord2 = 0.3; // Store the vertex position x coordinate (Third triangle's third vertex)
		float LXValue = m_XValue + XCoord;
		float RXValue = m_XValue + XCoord2;

		// Switch button
		if (RXValue >= 1) {
			m_Switch = 0;
		} else if (LXValue <= -1) {
			m_Switch = 1;
		}

		// Adding x value
		if (m_Switch == 1) {
			m_XValue += i;
		}
		else if (m_Switch == 0) {
			m_XValue -= i;
		}
		
		m_Shader.SetUniform1f("u_Value", m_XValue);

		const float TopVertPosXVal = 0.5;
		const float BotVertPosXVal = -0.5;
		float RXValue2 = m_YValue + TopVertPosXVal;
		float LXValue2 = m_YValue + BotVertPosXVal;

		if (RXValue2 >= 1) {
			m_Switch2 = 0;
		}
		else if (LXValue2 <= -1) {
			m_Switch2 = 1;
		}

		if (m_Switch2 == 1) {
			m_YValue += i;
		}
		else if (m_Switch2 == 0) {
			m_YValue -= i;
		}

		m_Shader.SetUniform1f("u_Value2", m_YValue);

		float timeValue3 = glfwGetTime();
		float XValue3 = (cos(timeValue3) / 2.0f) + 0.5;
		m_Shader.SetUniform1f("u_Value3", XValue3);

		// Draw first triangle
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 9));

	}

	void TestTexture2D::OnImGuiRender()
	{	
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
	
}