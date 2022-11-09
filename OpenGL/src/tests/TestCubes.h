#pragma once
#include "Test.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include <memory>

namespace test {

	class TestCubes : public Test
	{
	public:
		TestCubes();
		~TestCubes();

		void OnUpdate(float deltaTime) override;
		void OnRender(GLFWwindow* window) override;
		void OnImGuiRender() override;

		void processInput(GLFWwindow* window);
		void calcFrame();

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;

		glm::mat4 m_Proj;
		glm::vec3 m_TranslationA;
		glm::vec3 cubePositions[10];

		glm::vec3 m_CameraPos;
		glm::vec3 m_CameraFront;
		glm::vec3 m_CameraUp;


		float m_DeltaTime;	
		float m_LastFrame;
		float m_ClearColor[4];
	};

}