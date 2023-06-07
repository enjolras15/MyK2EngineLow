#include "k2EngineLowPreCompile.h"
#include "Light.h"

namespace nsK2EngineLow{

	void SceneLight::Init() {

		//Ç‡Ç§äÁíÜÉÅÉìÉoÇ‹Ç›ÇÍÇ‚
		m_light.ligDirection.x = 1.0f;
		m_light.ligDirection.y = -1.0f;
		m_light.ligDirection.z = -1.0f;

		m_light.ligDirection.Normalize();

		m_light.ligcolor.x = 0.0f;
		m_light.ligcolor.y = 0.0f;
		m_light.ligcolor.z = 0.0f;

		m_light.eyePos = g_camera3D->GetPosition();

		m_light.ambientlight.x = 0.3f;
		m_light.ambientlight.y = 0.3f;
		m_light.ambientlight.z = 0.3f;

		m_light.ptPosition.x = 0.0f;
		m_light.ptPosition.y = 0.0f;
		m_light.ptPosition.z = 0.0f;

		m_light.ptColor.x = 0.0f;
		m_light.ptColor.y = 0.0f;
		m_light.ptColor.z = 0.0f;

		//Ç†Ç†ÅAëÅÇ≠Vector3Ç‹Ç›ÇÍÇ…Ç»ÇÎÇ§Ç∫

		m_light.spPosition = Vector3{ 0.0f,50.0f,0.0f };

		m_light.spColor = Vector3{ 10.0f,10.0f,10.0f };

		m_light.spDirection = Vector3{ 1.0f,-1.0f,1.0f };
		m_light.spDirection.Normalize();

		m_light.spRange = 0.0f;
		m_light.spAngle = Math::DegToRad(150.0f);

		m_light.groundColor.x = 0.7f;
		m_light.groundColor.y = 0.7f;
		m_light.groundColor.z = 0.3f;

		m_light.skyColor.x = 0.15f;
		m_light.skyColor.y = 1.0f;
		m_light.skyColor.z = 0.0f;

	}


}