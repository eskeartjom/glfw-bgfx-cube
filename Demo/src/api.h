#pragma once

#include <cube.h>

namespace ea {

	class api {

	public:

		static api& Instance() {
			return instance;
		}

	    void Init(Cube* cubeObj){
			cube = cubeObj;
		}

		void Stop() {
			cube->isRunning = false;
		}

	private:
		api(){}

		static api instance;

		Cube* cube;

		
	};

}