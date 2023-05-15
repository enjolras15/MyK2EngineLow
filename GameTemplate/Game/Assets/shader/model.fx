
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
	float3 tangent : TANGENT;
	float3 biNormal : BINORMAL;
	SSkinVSIn skinVert;				//スキン用のデータ。
};

// ピクセルシェーダーへの入力
struct SPSIn
{
	float4 pos      : SV_POSITION;
	float3 normal   : NORMAL;
	float3 tangent : TANGENT;
	float3 biNormal: BIORMAL;
	float2 uv       : TEXCOORD0;
	float3 worldPos : TEXCOORD1;
	float3 normalInView : TEXCOORD2;

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

	float3 groundColor;
	float3 skyColor;
	float3 groundNormal;

};


////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
Texture2D<float4> g_normalMap : register(t1);
Texture2D<float4> g_specularMap : register(t2);
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

	psIn.normal = normalize(mul(mWorld, vsIn.normal));

	psIn.tangent = normalize(mul(mWorld,vsIn.tangent));
	psIn.biNormal = normalize(mul(mWorld,vsIn.biNormal));

	psIn.uv = vsIn.uv;

	psIn.normalInView = mul(mView, psIn.normal);

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
	float4 diffuseMap = g_albedo.Sample(g_sampler,psIn.uv);
	float3 normal = psIn.normal;

	float3 localNormal = g_normalMap.Sample(g_sampler,psIn.uv).xyz;
	localNormal = (localNormal - 0.5f) * 2.0;

	normal = psIn.tangent * localNormal.x + psIn.biNormal*localNormal.y+normal*localNormal.z;

	float3 diffDirection = CalcLambertDiffuse(ligDirection, ligColor, psIn.normal);
	float3 specDirection = CalcPhongSpecular(ligDirection, ligColor, psIn.worldPos, psIn.normal);

	float specPower = g_specularMap.Sample(g_sampler, psIn.uv).r;


	//半球ライトをドバーっと出して来た

	float t = dot(psIn.normal, groundNormal);

	t = (t + 1.0f) / 2.0f;

	float hemiLight = lerp(groundColor,skyColor,t);

	//リムライトまみれや

	float power1 = 1.0f - max(0.0f, dot(ligDirection,psIn.normal));
	float power2 = 1.0f - max(0.0f, psIn.normalInView.z * -1.0f);

	float limPower = power1 * power2;

	limPower = pow(limPower, 1.3f);

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
	//皆の影響率はね0.0以上の範囲にあるんだよ
    //影響率が下の方に集中するとね、そのaffectは下の世界に生まれ変わるんだって、嫌だねぇ
	if (affect < 0.0f) //今0.0未満になっていないaffectは、これからしないようにしようね。
	{
	
		//今0.0未満になっている良いaffectは、やめようね。
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


	specularLig *= specPower * 10.0f;

	float3 limColor = limPower * ligColor;

	float3 lig = diffuseLig + specularLig + ambientLight + hemiLight+limColor;

	//やりますねぇ

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