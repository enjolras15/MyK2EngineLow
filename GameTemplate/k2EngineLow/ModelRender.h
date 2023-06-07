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

		void OnRenderModel(RenderContext& rc) {

			model.Draw(rc);

		}


		void Draw(RenderContext& rc) {

			g_renderingEngine->AddModels(this);

		}

		void Update();

		ModelInitData modelInitData;

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

		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{

			animation.Play(animNo, interpolateTime);
		}


	private:

		Model model;
		Vector3 m_pos = Vector3::Zero;
		Quaternion m_rot = Quaternion::Identity;
		Vector3 m_scale = Vector3::One;



		Skeleton skeleton;
		AnimationClip* animationClip = nullptr;
		Animation animation;
		int m_numAnimationClips = 0;

	};

}

