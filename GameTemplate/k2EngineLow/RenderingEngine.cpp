#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {


	void RenderingEngine::ModelRendering(RenderContext& rc) {

		for (auto& modelsit : models) {

			modelsit->OnRenderModel(rc);


		}

	}


	void RenderingEngine::Execute(RenderContext& rc) {


		ModelRendering(rc);

	}


}