#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {

	RenderingEngine::RenderingEngine() {

		m_sceneLight.Init();
		InitRenderTarget();

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

	//この辺いにぃ、メインレンダリングターゲットきてるらしいっすよ
	void RenderingEngine::InitRenderTarget() {
		m_mainRenderTarget.Create(
			FRAME_BUFFER_W,
			FRAME_BUFFER_H,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);

	}


	void RenderingEngine::Execute(RenderContext& rc) {

		//描画するんだよ、あくしろよ
		ModelRendering(rc);
		SpriteRendering(rc);
		FontRendering(rc);

		//消さないと重くなってまずいですよ、じゃけん消しましょうね～
		m_models.clear();
		m_sprites.clear();
		m_fonts.clear();

	}


}