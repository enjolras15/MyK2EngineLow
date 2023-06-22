#pragma once
#include "Light.h"
#include "PostEffect.h"

namespace nsK2EngineLow {

	class ModelRender;
	class SpriteRender;
	class FontRender;
	class RenderContext;


	class RenderingEngine
	{
	public:

		RenderingEngine();

		void Execute(RenderContext& rc);

		void ModelRendering(RenderContext& rc);

		void SpriteRendering(RenderContext& rc);

		void FontRendering(RenderContext& rc);

		void AddModels(ModelRender* modelRender) {

			m_models.push_back(modelRender);

		}

		void AddSprites(SpriteRender* spriteRender) {

			m_sprites.push_back(spriteRender);

		}

		void AddFonts(FontRender* fontRender) {

			m_fonts.push_back(fontRender);

		}

		SceneLight& GetSceneLight()
		{
			return m_sceneLight;
		}


		void InitRenderTarget();

	private:
		std::vector<ModelRender*> m_models;
		std::vector<SpriteRender*> m_sprites;
		std::vector<FontRender*> m_fonts;

		RenderTarget m_mainRenderTarget;
		SceneLight	m_sceneLight;

		PostEffect m_postEffect;

	};

}

