#include "cube.h"
#include "data.h"

#include "api.h"

namespace ea {

	void glfw_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
			api::Instance().Stop();
	}

	Cube::Cube(uint32_t width, uint32_t height, bgfx::RendererType::Enum type)
		: width(width), height(height), type(type)
	{
		Create();
	}

	Cube::~Cube()
	{
		Destroy();
	}

	void Cube::Create()
	{
	

		glfwInit();

		window = glfwCreateWindow(width, height, "glfw-bgfx", nullptr, nullptr);

		glfwSetKeyCallback(window, glfw_keyCallback);

		#ifdef PLATFORM_WINDOWS
				nativeWindow = glfwGetWin32Window(window);
		#elif PLATFORM_MACOS
				nativeWindow = glfwGetCocoaWindow(window);
		#endif

		Vertex::init();

		bgfx::renderFrame();

		bgfx::PlatformData pd;
		pd.nwh = nativeWindow;
		bgfx::setPlatformData(pd);

		bgfx::Init init;
		init.type = type;
		init.resolution.width = width;
		init.resolution.height = height;
		init.resolution.reset = BGFX_RESET_VSYNC;
		bgfx::init(init);

		bgfx::setViewClear(0
			, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
			, 0x902290ff
			, 1.0f
			, 0
		);

		bgfx::setViewRect(0, 0, 0, width, height);

		vertexBuffer = bgfx::createVertexBuffer(
			bgfx::makeRef(vertecies, sizeof(vertecies)),
			Vertex::layout
		);

		indexBuffer = bgfx::createIndexBuffer(
			bgfx::makeRef(indecies, sizeof(indecies))
		);
		
		bgfx::ShaderHandle vs = loadShader("vs_cubes.bin");
		bgfx::ShaderHandle fs = loadShader("fs_cubes.bin");

		program = bgfx::createProgram(vs, fs, true);
		bgfx::setDebug(BGFX_DEBUG_TEXT);

	}

	void Cube::Run()
	{
		while (isRunning) {

			glfwPollEvents();

			bgfx::touch(0);

			const bx::Vec3 at = { 0.0f, 0.0f,   0.0f };
			const bx::Vec3 eye = { 0.0f, 0.0f, -5.0f };

			float view[16];
			bx::mtxLookAt(view, eye, at);
			float proj[16];
			bx::mtxProj(proj, 60.0f, width / height, 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
			bgfx::setViewTransform(0, view, proj);

			float mtx[16];
			bx::mtxRotateXY(mtx, counter * 0.01f, counter * 0.01f);
			bgfx::setTransform(mtx);

			bgfx::setVertexBuffer(0, vertexBuffer);
			bgfx::setIndexBuffer(indexBuffer);

			bgfx::submit(0, program);

			bgfx::dbgTextClear();

			bgfx::dbgTextPrintf(0, 0, 0x0f, "Press SPACE to to quit.");

			bgfx::frame();
			counter++;
		}
	}

	void Cube::Destroy()
	{
		bgfx::shutdown();
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	bgfx::ShaderHandle Cube::loadShader(std::string filename)
	{
		std::stringstream ss;

#ifdef PLATFORM_WINDOWS
		switch (bgfx::getRendererType())
		{
		case bgfx::RendererType::Direct3D9: ss << "./src/shaders/dx9/"; break;
		case bgfx::RendererType::Direct3D11:
		case bgfx::RendererType::Direct3D12: ss << "./src/shaders/dx11/"; break;
		case bgfx::RendererType::Metal: ss << "./src/shaders/metal/"; break;
		case bgfx::RendererType::OpenGL: ss << "./src/shaders/glsl/"; break;
		case bgfx::RendererType::Vulkan: ss << "./src/shaders/spirv/"; break;

		}
#elif PLATFORM_MACOS
#endif

		ss << filename;

		FILE* file = fopen(ss.str().c_str(), "rb");
		fseek(file, 0, SEEK_END);
		long fileSize = ftell(file);
		fseek(file, 0, SEEK_SET);

		const bgfx::Memory* mem = bgfx::alloc(fileSize + 1);
		fread(mem->data, 1, fileSize, file);
		mem->data[mem->size - 1] = '\0';
		fclose(file);

		return bgfx::createShader(mem);

	}

	


}