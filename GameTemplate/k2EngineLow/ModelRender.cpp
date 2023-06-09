﻿//やったぜ　投稿者　変態糞土方　８月１６（水）７時１４分２２秒
//昨日の８月１５日にいつもの浮浪者のおっさん（６０）と先日メールくれた汚れ好きの土方の兄ちゃん（４５）と
//わし（５３）の３人で県北にある川の土手の下で盛りあったぜ今日は明日が休みなんでコンビニで酒とつまみを買ってから
//滅多に人が来ないところなんで、そこでしこたま酒を飲んでからやり始めたんや

#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"

namespace nsK2EngineLow {

	ModelRender::ModelRender() {



	}

	void ModelRender::Init(
		const char* file,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis)
	{

		modelInitData.m_fxFilePath = "Assets/shader/model.fx";
		//バッファだって、嫌だねぇ
		modelInitData.m_expandConstantBuffer = &g_renderingEngine->GetSceneLight();
		modelInitData.m_expandConstantBufferSize = sizeof(g_renderingEngine->GetSceneLight());

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

			//アニメーションクリップ持ってんのかコラ
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

		//向きを変えるんだよ、UpAxisZになるんだよ
		modelInitData.m_modelUpAxis = enModelUpAxisZ;

		model.Init(modelInitData);




	}



	void ModelRender::Update() {
		//ぐるぐるしている
		model.UpdateWorldMatrix(m_pos, m_rot, m_scale);


		if (skeleton.IsInited()) {
			skeleton.Update(model.GetWorldMatrix());
		}

		animation.Progress(1.0 / 60.0f);

		//lightModel.UpdateWorldMatrix(light.ptPosition,g_quatIdentity,g_vec3One);

	}

}
