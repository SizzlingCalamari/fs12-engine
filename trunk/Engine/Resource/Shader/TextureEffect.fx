float4x4	gWorld;
float4x4	gWVP;

texture		tex1;
bool		hasTexture = true;

float3		gLightPosition;

float4 gDiffuseMtrl;	
float4 gDiffuseLight;	

// texture sampler
sampler		samp1
{
	Texture = <tex1>;
	MinFilter = ANISOTROPIC;
	MagFilter = ANISOTROPIC;
	MipFilter = ANISOTROPIC;
	AddressU  = WRAP;
	AddressV  = WRAP;
};
	
struct OutputVS
{
    float4 posH		: POSITION0;
    float2 texCoord0: TEXCOORD0;
    float3 posWorld: TEXCOORD1;
	float3 normal: TEXCOORD2;
};

OutputVS TransformVS(float3 posLocal:POSITION0, float3 normalL : NORMAL0, float2 uv0:TEXCOORD0)
{
	OutputVS Out = (OutputVS)0;

    Out.posH = mul(float4(posLocal, 1.0f), gWVP);
    
    float3 posWorld = mul(float4(posLocal, 1.0f), gWorld).xyz;

	Out.texCoord0 = uv0;

	float3 normalW = mul(float4(normalL,0.0f), gWorld).xyz;

	Out.normal = normalW;
	Out.posWorld = posWorld;

    return Out;
}

float4 TransformPS(OutputVS input):COLOR
{
	input.normal = normalize(input.normal);
    
    float3 lightDirection = (gLightPosition - input.posWorld);
    
    lightDirection = normalize(lightDirection);

	float lightAmount = saturate(dot(lightDirection, input.normal));

	float4 diffuse = lightAmount * (gDiffuseLight);// * gMaterialDiffuse);

	diffuse.a = 1.0f;

    float4 texCol = tex2D(samp1, input.texCoord0);
	if(!hasTexture)
	{
		return diffuse;
	}
	else
	{
		return diffuse * texCol;
	}
    
    return texCol;
}

technique Basic
{
    pass P0
    {
        vertexShader = compile vs_3_0 TransformVS();
        pixelShader  = compile ps_3_0 TransformPS();
    }
}