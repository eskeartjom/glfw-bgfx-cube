
#include "cube.h"

#include "api.h"

ea::api ea::api::instance;

int main() {

	ea::Cube* cube = new ea::Cube(1280, 720, bgfx::RendererType::Direct3D11);

	ea::api::Instance().Init(cube);

	cube->Run();
	delete cube;
}