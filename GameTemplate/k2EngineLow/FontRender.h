#pragma once

namespace nsK2EngineLow {

	class FontRender
	{
	public:
		static const int MAX_TEXT_SIZE = 256;
		void SetText(const wchar_t* text)
		{
			swprintf_s(m_text, text);
		}

		void SetPosition(const Vector3& position)
		{
			m_pos = position;
		}

		void SetScale(const float scale)
		{
			m_scale = scale;
		}

		void SetColor(const Vector4& color)
		{
			m_color = color;
		}

		void SetPivot(const Vector2& pivot)
		{
			m_pivot = pivot;
		}

		void SetRotation(const float rot) {

			m_rot = rot;

		}

		void Draw(RenderContext& rc) {

			g_renderingEngine->AddFonts(this);

		}

		void OnRenderFont(RenderContext& rc) {


			font.Begin(rc);
			font.Draw(m_text, Vector2(m_pos.x, m_pos.y), m_color, m_rot, m_scale, m_pivot);
			font.End(rc);
		}

	private:
		wchar_t m_text[MAX_TEXT_SIZE];
		Vector3 m_pos = Vector3::Zero;
		float m_scale = 1.0f;
		Vector4 m_color=g_vec4White;
		float	m_rot = 0.0f;
		Vector2	m_pivot = Sprite::DEFAULT_PIVOT;

		Font font;

	};

}
