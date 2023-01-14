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
	 
		unsigned int m_Buffer[3];	

		float m_XValue = 0;
		float m_YValue = 0;

		int m_Switch2 = 0;
		int m_Switch = 1;

	};

}