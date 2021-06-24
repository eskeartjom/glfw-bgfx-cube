#pragma once
#include <platfrom.h>


#ifdef PLATFORM_WINDOWS
	#define GLFW_EXPOSE_NATIVE_WIN32
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif // !NOMINMAX
#elif PLATFORM_MACOS
	#define GLFW_EXPOSE_NATIVE_COCOA
#endif



#include <GLFW/glfw3.h>;
#include <GLFW/glfw3native.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <bx/math.h>

#include <string>
#include <sstream>
#include <filesystem>
#include <iostream>

namespace ea {

	class Cube {

	public:

		Cube(uint32_t width, uint32_t height, bgfx::RendererType::Enum type);
		~Cube();

		void Create();
		void Run();
		void Destroy();

		bgfx::ShaderHandle loadShader(std::string filename);

		bool isRunning = true;


	private:

	

		bgfx::RendererType::Enum type;
		uint32_t width = 1280;
		uint32_t height = 720;

		GLFWwindow* window;
		void* nativeWindow;

		bgfx::VertexBufferHandle vertexBuffer;
		bgfx::IndexBufferHandle indexBuffer;
		bgfx::ProgramHandle program;

		bgfx::RendererType::Enum renderAPI;
		const char* renderAPIName;

		uint64_t counter = 0;

		

	};

}