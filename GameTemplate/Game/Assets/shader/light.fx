/*!
 * @brief	シンプルなモデルシェーダー。
 */

 //頂点シェーダーへの入力。

struct SSkinVSIn {
	int4  Indices  	: BLENDINDICES0;
	float4 Weights  : BLENDWEIGHT0;
};

struct SVSIn
{
	float4 pos      : POSITION;
	float3 normal   : NORMAL;
	float2 uv       : TEXCOORD0;
	SSkinVSIn skinVert;				//スキン用のデータ。
};

// ピクセルシェーダーへの入力
struct SPSIn
{
	float4 pos      : SV_POSITION;
	float3 normal   : NORMAL;
	float2 uv       : TEXCOORD0;
	float3 worldPos : TEXCOORD1;

};

////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

cbuffer DirectionLightCb : register(b1) {

	float3 ligDirection;
	float3 ligColor;

	float3 ptPosition;
	float3 ptColor;
	float ptRange;

	float3 spPosition;
	float3 spColor;
	float spRange;
	float3 spDirection;
	float spAngle;

	float3 eyePos;
	float3 ambientLight;


};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
sampler g_sampler : register(s0);	//サンプラステート。

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);

/// <summary>
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn, uniform bool hasSkin)
{

	SPSIn psIn;
	float4x4 m;

    m = mWorld;

	psIn.pos = mul(m, vsIn.pos);
	psIn.worldPos = vsIn.pos;
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);

	psIn.normal = mul(mWorld, vsIn.normal);

	psIn.uv = vsIn.uv;

	return psIn;
}

float4 PSMain(SPSIn psIn) : SV_Target0
{

	float3 diffDirection = CalcLambertDiffuse(ligDirection, ligColor, psIn.normal);
	float3 specDirection = CalcPhongSpecular(ligDirection, ligColor, psIn.worldPos, psIn.normal);

	float3 ligDir = psIn.worldPos - ptPosition;

	ligDir = normalize(ligDir);

	float3 diffPoint = CalcLambertDiffuse(ligDir,ptColor,psIn.normal);

	float3 specPoint = CalcPhongSpecular(ligDir,ptColor,psIn.worldPos,psIn.normal);

	float3 distance = length(psIn.worldPos - ptPosition);

	float affect = 1.0f - 1.0f / ptRange * distance;

	if (affect < 0.0f)
	{
		affect = 0.0f;
	}

	affect = pow(affect, 3.0f);

	diffPoint *= affect;
	specPoint *= affect;

	//スポットライトって知ってるかな？

	ligDir = psIn.worldPos - spPosition;

	ligDir = normalize(ligDir);

	//例えばランバート拡散反射する位置と角度を持ったライトとか

	float3 diffSpot = CalcLambertDiffuse(ligDir,spColor,psIn.normal);

	//あるいはPhong鏡面反射する方向と色を持ったライトといったことをスポットライトというんだ

	float3 specSpot = CalcPhongSpecular(ligDir,spColor,psIn.worldPos,psIn.normal);

	distance = length(psIn.worldPos - spPosition);

	affect = 1.0f - 1.0f / spRange * distance;
	//皆の影響率は0.0以上の範囲にあるんだよ
    //影響率が下の方に集中するとね、その子は下の世界に生まれ変わるんだって、嫌だねぇ
	if (affect < 0.0f) //今0.0未満になっていない子は、これからしないようにしようね。
	{
	
		//今0.0未満になっている良い子は、やめようね。
		affect = 0.0f;
	}

	affect = pow(affect, 3.0f);

	diffSpot *= affect;
	specSpot *= affect;

	float angle = dot(ligDir,spDirection);
	angle = abs(acos(angle));

	affect = 1.0f - 1.0f / spAngle * angle;

	if (affect < 0.0f)
	{
		affect = 0.0f; //やめようね
	}

	affect = pow(affect, 5.0f);

	diffSpot *= affect;
	specSpot *= affect;

	float3 diffuseLig = diffPoint + diffDirection+diffSpot;
	float3 specularLig = specPoint + specDirection+specSpot;

	float3 lig = diffuseLig + specularLig + ambientLight;

	//ああ～早くライティングまみれになろうぜ。

	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);

	albedoColor.xyz *= lig;

	return albedoColor;
}


float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{

	float t = dot(normal, lightDirection) * -1.0f;

	if (t < 0.0f) {

		t = 0.0f;

	}

	return lightColor * t;
}

float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{

	float3 refVec = reflect(lightDirection, normal);

	float3 toEye = eyePos - worldPos;

	toEye = normalize(toEye);

	float t = dot(refVec, toEye);

	if (t < 0.0) {

		t = 0.0f;

	}

	t = pow(t, 5.0f);

	return lightColor * t;

}