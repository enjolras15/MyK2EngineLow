#pragma once

namespace nsK2EngineLow {

	 class ModelRender
	{
	public:
		ModelRender();

		void Init(
			const char* file,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ);

		void Draw(RenderContext& rc);

		void Update();

		ModelInitData modelInitData;

		struct DirectionLight
		{

			Vector3 ligDirection;
			float pad;
			Vector3 ligcolor;
			float pad1;

			Vector3 ptPosition;
			float pad2;
			Vector3 ptColor;
			float ptRange = 0.0f;

			Vector3 eyePos;
			float pad3;
			Vector3 ambientLight;

		};

		void SetPosition(const Vector3& pos)
		{
			m_pos = pos;
		}

		void SetRotation(const Quaternion& rotation)
		{
			m_rot = rotation;
		}

		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}

		DirectionLight directionLig;


		void PointLightRnage(const float& range)
		{
			directionLig.ptRange = range;
		}

		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{


			animation.Play(animNo, interpolateTime);
		}

	private:

		Model model,lightModel;
		Vector3 m_pos = Vector3::Zero;
		Quaternion m_rot = Quaternion::Identity;
		Vector3 m_scale = Vector3::One;

		Skeleton skeleton;
		AnimationClip* animationClip = nullptr;
		Animation animation;
		int m_numAnimationClips = 0;

	};

}

