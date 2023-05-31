//やったぜ　投稿者　変態糞土方　８月１６（水）７時１４分２２秒
//昨日の８月１５日にいつもの浮浪者のおっさん（６０）と先日メールくれた汚れ好きの土方の兄ちゃん（４５）と
//わし（５３）の３人で県北にある川の土手の下で盛りあったぜ今日は明日が休みなんでコンビニで酒とつまみを買ってから
//滅多に人が来ないところなんで、そこでしこたま酒を飲んでからやり始めたんや

#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"

namespace nsK2EngineLow {

	ModelRender::ModelRender() {

		//もう顔中メンバまみれや
		light.ligDirection.x = 1.0f;
		light.ligDirection.y = -1.0f;
		light.ligDirection.z = -1.0f;

		light.ligDirection.Normalize();

		light.ligcolor.x = 0.0f;
		light.ligcolor.y = 0.0f;
		light.ligcolor.z = 0.0f;

		light.eyePos = g_camera3D->GetPosition();

		light.ambientLight.x = 0.3f;
		light.ambientLight.y = 0.3f;
		light.ambientLight.z = 0.3f;

		light.ptPosition.x = 0.0f;
		light.ptPosition.y = 0.0f;
		light.ptPosition.z = 0.0f;

		light.ptColor.x = 0.0f;
		light.ptColor.y = 0.0f;
		light.ptColor.z = 0.0f;

		//ああ、早くVector3まみれになろうぜ

		light.spPosition = Vector3{ 0.0f,50.0f,0.0f };

		light.spColor = Vector3{ 10.0f,10.0f,10.0f };

		light.spDirection = Vector3{ 1.0f,-1.0f,1.0f };
		light.spDirection.Normalize();

		light.spRange = 0.0f;
		light.spAngle = Math::DegToRad(150.0f);

		light.groundColor.x = 0.7f;
		light.groundColor.y = 0.7f;
		light.groundColor.z = 0.3f;

		light.skyColor.x = 0.15f;
		light.skyColor.y = 1.0f;
		light.skyColor.z = 0.0f;


	}

	void ModelRender::Init(
		const char* file,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis)
	{

		modelInitData.m_fxFilePath = "Assets/shader/model.fx";
		//バッファだって、嫌だねぇ
		modelInitData.m_expandConstantBuffer = &light;
		modelInitData.m_expandConstantBufferSize = sizeof(light);

		if (animationClips == nullptr) {
			//滅多にスキンが来ないところなんで
			modelInitData.m_vsEntryPointFunc = "VSMain";
		}
		else {
			//コンビニでスキンとアニメーションを買ってから
			modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";

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
		//ぐるぐるしている
		model.UpdateWorldMatrix(m_pos, m_rot, m_scale);


		if (skeleton.IsInited()) {
			skeleton.Update(model.GetWorldMatrix());
		}

		animation.Progress(1.0 / 60.0f);

		lightModel.UpdateWorldMatrix(light.ptPosition,g_quatIdentity,g_vec3One);

	}

}
