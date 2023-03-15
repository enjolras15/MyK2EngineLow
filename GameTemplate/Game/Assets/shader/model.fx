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
//float4x4 CalcSkinMatrix(SSkinVSIn skinVert) ;

float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
	float4x4 skinning = 0;
	float w = 0.0f;
	[unroll]
	for (int i = 0; i < 3; i++)
	{
		skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
		w += skinVert.Weights[i];
	}

	skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);

	return skinning;
}


/// <summary>
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{

	SPSIn psIn;
	float4x4 m;

	if (hasSkin) {
		m = CalcSkinMatrix(vsIn.skinVert);
	}
	else {
		m = mWorld;
	}

	psIn.pos = mul(m, vsIn.pos);
	psIn.worldPos = vsIn.pos;
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);

	psIn.normal = mul(mWorld, vsIn.normal);

	psIn.uv = vsIn.uv;

	return psIn;
}

/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, false);
}
/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSSkinMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, true);
}

float4 PSMain(SPSIn psIn) : SV_Target0
{

	float3 diffDirection = CalcLambertDiffuse(ligDirection, ligColor, psIn.normal);
	float3 specDirection = CalcPhongSpecular(ligDirection, ligColor, psIn.worldPos, psIn.normal);

	float3 ligDir = psIn.worldPos - ptPosition;

	ligDir = normalize(ligDir);

	float3 diffPoint = CalcLambertDiffuse(
		ligDir,    
		ptColor,  
		psIn.normal 
	);

	float3 specPoint = CalcPhongSpecular(
		ligDir,     
		ptColor,     
		psIn.worldPos,  
		psIn.normal   
	);

	float3 distance = length(psIn.worldPos - ptPosition);

	float affect = 1.0f - 1.0f / ptRange * distance;

	if (affect < 0.0f)
	{
		affect = 0.0f;
	}

	affect = pow(affect, 3.0f);

	diffPoint *= affect;
	specPoint *= affect;

	float3 diffuseLig = diffPoint + diffDirection;
	float3 specularLig = specPoint + specDirection;

	float3 lig = diffuseLig + specularLig + ambientLight;

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