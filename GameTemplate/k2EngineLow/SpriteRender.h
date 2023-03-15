#pragma once

namespace nsK2EngineLow {

	class SpriteRender
	{

	public:
		void Init(const char* file, const float w, const float h, AlphaBlendMode alphaBlendMode = AlphaBlendMode_Trans);

		void SetPosition(const Vector3& pos) {

			m_pos = pos;

		}

		void SetScale(const Vector3& scale) {

			m_scale = scale;

		}

		void SetRotation(const Quaternion& rot) {

			m_rot = rot;

		}

		const Quaternion& GetRotation() const
		{
			return m_rot;
		}

		void SetPivot(const Vector2& pivot) {

			m_pivot = pivot;

		}


		void Update()
		{
			m_sprite.Update(m_pos,
				m_rot,
				m_scale,
				m_pivot);
		}

		void Draw(RenderContext& rc);

	private:

		Sprite m_sprite;
		Vector3 m_pos = Vector3::Zero;
		Vector3 m_scale = Vector3::One;
		Vector2 m_pivot = Sprite::DEFAULT_PIVOT;
		Quaternion m_rot = Quaternion::Identity;
	};

}

