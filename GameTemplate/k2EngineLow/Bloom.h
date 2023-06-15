#pragma once

namespace nsK2EngineLow{

	class Bloom
	{

	public:
		void Init(RenderTarget& mainRenderTarget);

		void OnRender(RenderContext& rc,RenderTarget& mainRenderTarget);

	private:
		void InitRenderTarget(RenderTarget& mainRenderTarget);

		void InitLuminanceSprite(RenderTarget& mainRenderTarget);

		void InitFinalSprite(RenderTarget& mainRendeeTarget);

		void InitGaussianBlur();

		RenderTarget m_luminnceRenderTarget;

		Sprite m_luminnceSprite;

		Sprite m_finalSprite;

		//俺のブルァーに付いてこい
		GaussianBlur m_gaussianBlur[4];

	};

}
