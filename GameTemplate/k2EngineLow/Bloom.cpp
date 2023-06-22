#include "k2EngineLowPreCompile.h"
#include "Bloom.h"

//‚±‚ê‚à‚¤‚í‚©‚ñ‚Ë‚¥‚È

namespace BloomConst
{
	const int BLUR_POWER = 10;
}

namespace nsK2EngineLow {

	void Bloom::Init(RenderTarget& mainRenderTarget) {

		InitRenderTarget(mainRenderTarget);
		InitLuminanceSprite(mainRenderTarget);
		InitGaussianBlur();
		InitFinalSprite(mainRenderTarget);

	}

	void Bloom::InitRenderTarget(RenderTarget& mainRenderTarget) {

		m_luminnceRenderTarget.Create(
			mainRenderTarget.GetWidth(), 
			mainRenderTarget.GetHeight(),
			1,
			1,
			mainRenderTarget.GetColorBufferFormat(),
			DXGI_FORMAT_D32_FLOAT
		);

	}

	void Bloom::InitLuminanceSprite(RenderTarget& mainRenderTarget) {

		SpriteInitData luminanceSpriteInitData;
		luminanceSpriteInitData.m_fxFilePath="Assets/shader/postEffect/postEffect.fx";
		luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";
		luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";

		luminanceSpriteInitData.m_width = m_luminnceRenderTarget.GetWidth();
		luminanceSpriteInitData.m_height = m_luminnceRenderTarget.GetHeight();

		luminanceSpriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();

		luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		m_luminnceSprite.Init(luminanceSpriteInitData);

	}
	
	void Bloom::InitFinalSprite(RenderTarget& mainRenderTarget) {

		SpriteInitData finalSpriteInitData;
		finalSpriteInitData.m_textures[0] = &m_gaussianBlur[0].GetBokeTexture();

		finalSpriteInitData.m_width = mainRenderTarget.GetWidth();
		finalSpriteInitData.m_height = mainRenderTarget.GetHeight();

		finalSpriteInitData.m_fxFilePath = "Assets/shader/postEffect/postEffect.fx";
		finalSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";

		finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;

		finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		m_finalSprite.Init(finalSpriteInitData);

	}

	void Bloom::InitGaussianBlur() {

		
		m_gaussianBlur[0].Init(&m_luminnceRenderTarget.GetRenderTargetTexture());


	}

	void Bloom::OnRender(RenderContext& rc, RenderTarget& mainRenderTarget) {

		rc.WaitUntilFinishDrawingToRenderTarget(m_luminnceRenderTarget);

		m_gaussianBlur[0].ExecuteOnGPU(rc, BloomConst::BLUR_POWER);

		rc.WaitUntilFinishDrawingToRenderTarget(m_luminnceRenderTarget);
		rc.SetRenderTargetAndViewport(mainRenderTarget);

		m_finalSprite.Draw(rc);

		rc.WaitUntilFinishDrawingToRenderTarget(m_luminnceRenderTarget);

	}

}