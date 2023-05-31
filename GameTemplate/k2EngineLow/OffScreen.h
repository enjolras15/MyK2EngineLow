#pragma once
#include "stdio.h"

namespace nsK2EngineLow {

	class OffScreen
	{

	public:

		OffScreen();
		void Draw(RenderContext& rc);

		void Init(
			const char* file,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ);

	    std::vector<const char*> files;

		struct Light {

			Vector3 ligDirection;
			float pad;
			Vector3 ligcolor;
			float pad1;

			Vector3 ptPosition;
			float pad2;
			Vector3 ptColor;
			float ptRange = 0.0f;

			//スポットライト
			Vector3 spPosition;
			float pad3;
			Vector3 spColor;
			float spRange;
			Vector3 spDirection;
			float spAngle;

			Vector3 eyePos;
			float pad4;
			Vector3 ambientLight;
			float pad5;

			Vector3 groundColor;
			float pad6;
			Vector3 skyColor;
			float pad7;
			Vector3 groundNormal;

		};

		const int LIGHT_NUM = 6;

		Light light;

	private:
		RenderTarget offscreenRenderTarget;
		Model model;
		Model models[99];

	};

}

