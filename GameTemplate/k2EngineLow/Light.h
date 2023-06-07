#pragma once
namespace nsK2EngineLow {



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
			Vector3 ambientlight;
			float pad5;

			Vector3 groundColor;
			float pad6;
			Vector3 skyColor;
			float pad7;
			Vector3 groundNormal;

		};

		//const int LIGHT_NUM = 6

		class SceneLight
		{
		public:
			void Init();

			Light& GetSceneLight()
			{
				return m_light;
			}


			//void SetPointLightRnage(const float& range)
			//{
			//	light.ptRange = range;
			//}

		private:
			Light m_light;
     	};

}
