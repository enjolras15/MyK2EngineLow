#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {

	RenderingEngine::RenderingEngine() {

		m_sceneLight.Init();


	}

	void RenderingEngine::ModelRendering(RenderContext& rc) {

		for (auto& modelsit : m_models) {

			modelsit->OnRenderModel(rc);

		}

	}

	void RenderingEngine::SpriteRendering(RenderContext& rc) {

		for (auto& spritesit: m_sprites) {

			spritesit->OnRenderSprite(rc);


		}

	}

	void RenderingEngine::FontRendering(RenderContext& rc) {

		for (auto& fontit : m_fonts) {

			fontit->OnRenderFont(rc);


		}

	}


	void RenderingEngine::Execute(RenderContext& rc) {

		//描画するんだよ、あくしろよ
		ModelRendering(rc);
		SpriteRendering(rc);
		FontRendering(rc);

		//消さないと重くなってまずいですよ、じゃけん消しましょうね〜
		m_models.clear();
		m_sprites.clear();
		m_fonts.clear();

	}


}