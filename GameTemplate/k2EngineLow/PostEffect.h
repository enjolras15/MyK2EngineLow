#pragma once
//#include "Bloom.h"
namespace nsK2EngineLow{

	class PostEffect
	{
	public:
		void Init(RenderTarget& rc);
		void Render(RenderContext& rc, RenderTarget& mainRenderTarget);

	private:
		void InitBloom(RenderContext& mainRenderTarget);

		//Bloom m_bloom

	};

}

