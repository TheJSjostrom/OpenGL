#include "TestSquare2D.h"

#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"

namespace test {

	TestSquare2D::TestSquare2D()
		: m_Proj(glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 100.0f)),
		m_TranslationA(0, 0, -3)
	 
	{

		float positions[] = {
			0.5f, 0.5f, 0.0f,   0.0f, 0.0f,
			0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
		   -0.5f, -0.5f, 0.0f,   1.0f, 1.0f,
		   -0.5f,  0.5f, 0.0f,   0.0f, 1.0f,
		};

		unsigned int indicies[] = {
			0, 1, 2,
			2, 3, 0
		};

		glEnable(GL_DEPTH_TEST);
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 5 * sizeof(float));
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

	TestSquare2D::~TestSquare2D()
	{
	}

	void TestSquare2D::OnUpdate(float deltaTime)
	{
	}

	void TestSquare2D::OnRender(GLFWwindow* window)
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Renderer renderer;

		m_Texture->Bind();
		{
			glm::mat4 trans = glm::mat4(1.0f);
			trans = glm::translate(trans, m_TranslationA);
			// trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 mvp = m_Proj * trans;
			glm::vec4 vec = glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);
			glm::vec4 pos = mvp * vec;

			std::cout << "X-value: " << pos.x << " " << "Y-value: " << pos.y << " " << "Z-value: " << pos.w << " " << "W-value: " << pos.z << std::endl;

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}


	}

	void TestSquare2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, -3.0f, 3.0f);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}