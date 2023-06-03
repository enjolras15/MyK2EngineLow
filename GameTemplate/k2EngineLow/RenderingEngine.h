#pragma once

namespace nsK2EngineLow {

	class ModelRender;
	class RenderContext;

	class RenderingEngine
	{
	public:

		void Execute(RenderContext& rc);

		void ModelRendering(RenderContext& rc);

		void AddModels(ModelRender* modelRender) {

			models.push_back(modelRender);

		}

	private:
		std::vector<ModelRender*> models;

	};

}

