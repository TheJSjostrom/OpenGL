#include "TestCube3D.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"

namespace test {

	TestCube3D::TestCube3D() : m_ClearColor{ 0.2f, 0.3f, 0.8f, 1.0f }, m_TranslationA(0.0f, 0.0f, -3.0f)
	{

		float positions[] = {
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

		unsigned int indicies[] = {
			0, 1, 2,
			2, 3, 0
		};
		glEnable(GL_DEPTH_TEST);

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 36 * 5 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indicies, 6);

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.0f, 0.3f, 0.8f, 1.0f);

		m_Texture = std::make_unique<Texture>("res/textures/wooden.jpg");
		m_Shader->SetUniform1i("u_Texture", 0);

	}

	TestCube3D::~TestCube3D()
	{
	}

	void TestCube3D::OnUpdate(float deltaTime)
	{
	}

	void TestCube3D::OnRender(GLFWwindow* window)
	{

		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		GLCall(glClearColor(m_ClearColor[0], greenValue, m_ClearColor[2], m_ClearColor[3]));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Renderer renderer;

		m_Texture->Bind();

		{
			// Camera transformation matrix
			const float radius = 5.0f;
			const glm::vec3 camDir = glm::vec3(0.0, 0.0, 0.0);
			const glm::vec3 camDirUp = glm::vec3(0.0, 1.0, 0.0);
			glm::vec3 camPos;

			camPos.x = sin(glfwGetTime()) * radius;
			camPos.y = 0;
			camPos.z = cos(glfwGetTime()) * radius;
			glm::mat4 view;
			view = glm::lookAt(camPos, camDir, camDirUp);

			// Object transformation matrix
			float angle = (float)glfwGetTime() * 7 * glm::radians(50.0f);
			const glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
			model = glm::rotate(model, angle, rotationAxis);
		 
			// Projection transformation matrix
			glm::mat4 proj = glm::perspective(glm::radians(50.0f), 800.0f / 600.0f, 0.1f, 100.0f);

			// Creating mvp matrix
			glm::mat4 mvp = proj * view * model;

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}

		{ 
			const float radius = 5.0f;
			float camX = sin(glfwGetTime()) * radius;
			float camZ = cos(glfwGetTime()) * radius;
			glm::mat4 view;
			view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

			glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(1.75f, 0.0f, 0.0f));
			model = glm::rotate(model, (float)glfwGetTime() * 7 * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			 
			glm::mat4 proj = glm::perspective(glm::radians(50.0f), 800.0f / 600.0f, 0.1f, 100.0f);
			glm::mat4 mvp = proj * view * model;

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}

	}

	void TestCube3D::OnImGuiRender()
	{
		ImGui::ColorEdit4("Select color", m_ClearColor);
	 
		ImGui::SliderFloat2("Change X & Y postion A", &m_TranslationA.x, -2.0f, 2.0f);
		ImGui::SliderFloat("Zoom in & out A", &m_TranslationA.z, -1.0f, -10.0f);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}