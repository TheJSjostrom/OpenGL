#pragma once
#include "Test.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include <memory>

namespace test {

	class TestTexture2D : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender(GLFWwindow* window) override;
		void OnImGuiRender() override;

	private:
		Shader m_Shader, m_Shader2;
	 
		unsigned int m_Buffer[5], m_VAO[5];
		unsigned int texture[2];
		float m_XValue = 0;
		int m_Switch = 0;
		int m_Switch2 = 0;
		float m_XPos = -30.0f;
		float m_x = 0;
		unsigned int m_texture;
		unsigned int m_texture2;

		glm::vec3 cameraPos = glm::vec3(0.0f, 0.5f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	};

}