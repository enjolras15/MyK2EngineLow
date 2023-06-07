#include "k2EngineLowPreCompile.h"
#include "SpriteRender.h"

namespace nsK2EngineLow {

	void SpriteRender::Init(const char* file,const float w, const float h, AlphaBlendMode alphaBlendMode) {

		SpriteInitData initData;

		initData.m_ddsFilePath[0]=file;

		initData.m_fxFilePath = "Assets/shader/sprite.fx";

		initData.m_width = static_cast<UINT>(w);
		initData.m_height = static_cast<UINT>(h);
		initData.m_alphaBlendMode = alphaBlendMode;

		m_sprite.Init(initData);
	}



	}
