#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"

namespace nsK2EngineLow {

	ModelRender::ModelRender() {

		directionLig.ligDirection.x = 1.0f;
		directionLig.ligDirection.y = -1.0f;
		directionLig.ligDirection.z = -1.0f;

		directionLig.ligDirection.Normalize();

		directionLig.ligcolor.x = 0.5f;
		directionLig.ligcolor.y = 0.5f;
		directionLig.ligcolor.z = 0.5f;

		directionLig.eyePos = g_camera3D->GetPosition();

		directionLig.ambientLight.x = 0.3f;
		directionLig.ambientLight.y = 0.3f;
		directionLig.ambientLight.z = 0.3f;

		directionLig.ptPosition.x = 0.0f;
		directionLig.ptPosition.y = 0.0f;
		directionLig.ptPosition.z = 0.0f;

		directionLig.ptColor.x = 5.0f;
		directionLig.ptColor.y = 5.0f;
		directionLig.ptColor.z = 5.0f;

	}

	void ModelRender::Init(
		const char* file,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis)
	{

		modelInitData.m_fxFilePath = "Assets/shader/model.fx";

		modelInitData.m_expandConstantBuffer = &directionLig;
		modelInitData.m_expandConstantBufferSize = sizeof(directionLig);

		if (animationClips == nullptr) {
			modelInitData.m_vsEntryPointFunc = "VSMain";
		}
		else {
			modelInitData.m_vsEntryPointFunc = "VSSkinMain";

			std::string skeletonFilePath = file;
			int pos = (int)skeletonFilePath.find(".tkm");
			skeletonFilePath.replace(pos, 4, ".tks");
			skeleton.Init(skeletonFilePath.c_str());

			animationClip = animationClips;
			m_numAnimationClips = numAnimationClips;
			if (animationClip != nullptr) {
				animation.Init(
					skeleton,
					animationClip,
					m_numAnimationClips
				);
			}
			modelInitData.m_skeleton = &skeleton;
		}

		modelInitData.m_tkmFilePath = file;

		modelInitData.m_modelUpAxis = enModelUpAxisZ;

		model.Init(modelInitData);

	}

	void ModelRender::Draw(RenderContext& rc) {

		model.Draw(rc);


	}


	void ModelRender::Update() {

		model.UpdateWorldMatrix(m_pos, m_rot, m_scale);


		if (skeleton.IsInited()) {
			skeleton.Update(model.GetWorldMatrix());
		}

		animation.Progress(1.0 / 60.0f);


		lightModel.UpdateWorldMatrix(directionLig.ptPosition, g_quatIdentity, g_vec3One);

	}

}
