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
		Shader m_Shader, m_Shader2, m_Shader3;
	 
		unsigned int m_Buffer[4], m_VAO[5];
		unsigned int texture[2];
		
		int m_Switch = 0;
		float m_x = 0;

		unsigned int m_texture;
		unsigned int m_texture2;
		unsigned int m_texture3;
		unsigned int m_texture4;

		glm::vec3 cameraPos = glm::vec3(0.0f, 0.5f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::vec3 m_lightPos = glm::vec3(0.8f, 2.0f, 0.0f);
		glm::vec3 m_camPos = glm::vec3(2.0f, 3.0f, 5.0f);
	 
		float angle = 0.0f;

		glm::vec3 m_ObjectColor = glm::vec3(1.0f, 0.5f, 0.31f);
		glm::vec3 m_LightColor = glm::vec3(1.0f, 1.0f, 1.0f);
		float m_LightObjPos = 0.0f;

		glm::vec3 m_trans = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
		float m_rot = 0.0f;
	};

}