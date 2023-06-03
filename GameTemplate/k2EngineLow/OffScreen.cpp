#include "k2EngineLowPreCompile.h"
#include "OffScreen.h"
#include "stdio.h"

namespace nsK2EngineLow {

	OffScreen::OffScreen() {

		float color[4] = { 1,1,1,1 };


		offscreenRenderTarget.Create(
			1280,
			720,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_D32_FLOAT
		);

		//もう顔中メンバまみれや

		light.ambientLight.x = 0.3f;
		light.ambientLight.y = 0.3f;
		light.ambientLight.z = 0.3f;

		//ああ、早くVector3まみれになろうぜ

		light.groundColor.x = 0.7f;
		light.groundColor.y = 0.7f;
		light.groundColor.z = 0.3f;

		light.skyColor.x = 0.15f;
		light.skyColor.y = 1.0f;
		light.skyColor.z = 0.0f;

	}


	void OffScreen::Draw(RenderContext& rc) {

		RenderTarget* rtArray[] = { &offscreenRenderTarget };
		rc.WaitUntilToPossibleSetRenderTargets(1, rtArray);
		rc.SetRenderTargets(1, rtArray);
		rc.ClearRenderTargetViews(1, rtArray);

		for (int i = 0; i < 99; i++) {
			
			models[i].Draw(rc);

		}


		rc.WaitUntilFinishDrawingToRenderTargets(1, rtArray);

		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);


		model.Draw(rc);

	}

	void OffScreen::Init(
		const char* file,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis) {

		ModelInitData modelInitData;

		modelInitData.m_fxFilePath = "Assets/shader/model.fx";
		//バッファだって、嫌だねぇ
		modelInitData.m_expandConstantBuffer = &light;
		modelInitData.m_expandConstantBufferSize = sizeof(light);

		if (animationClips == nullptr) {
			//滅多にスキンが来ないところなんで
			modelInitData.m_vsEntryPointFunc = "VSMain";
		}
		else {
			////コンビニでスキンとアニメーションを買ってから
			//modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";

			//std::string skeletonFilePath = file;
			//int pos = (int)skeletonFilePath.find(".tkm");
			//skeletonFilePath.replace(pos, 4, ".tks");
			//skeleton.Init(skeletonFilePath.c_str());

			//animationClip = animationClips;
			//m_numAnimationClips = numAnimationClips;

			//if (animationClip != nullptr) {
			//	animation.Init(
			//		skeleton,
			//		animationClip,
			//		m_numAnimationClips
			//	);
			//}
			//modelInitData.m_skeleton = &skeleton;
		}

		modelInitData.m_tkmFilePath = file;

		modelInitData.m_modelUpAxis = enModelUpAxisZ;

		model.Init(modelInitData);

	
		
		for (int i = 0; i < files.size(); i++) {

			modelInitData.m_tkmFilePath = files.at(i);

			modelInitData.m_fxFilePath = "Assets/shader/model.fx";
			//バッファだって、嫌だねぇ
			modelInitData.m_expandConstantBuffer = &light;
			modelInitData.m_expandConstantBufferSize = sizeof(light);
			models[i].Init(modelInitData);

		}



		//オフスクリーンの世界に生まれ変わるんだって、嫌だねぇ
		model.ChangeAlbedoMap(
			"",
			offscreenRenderTarget.GetRenderTargetTexture()
		);


	}

}