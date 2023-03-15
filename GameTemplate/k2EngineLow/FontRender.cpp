#include "k2EngineLowPreCompile.h"
#include "FontRender.h"

namespace nsK2EngineLow {

	void FontRender::Draw(RenderContext& rc) {


		font.Begin(rc);
		font.Draw(m_text, Vector2(m_pos.x, m_pos.y), m_color, m_rot, m_scale, m_pivot);
		font.End(rc);
	}


}
