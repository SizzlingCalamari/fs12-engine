#include "BaseShader.h"
#include "..\Wrapper\Direct3D.h"

#include "Mesh.h"

BaseShader::BaseShader()
{
	effect = NULL;
	
	ID3DXBuffer	*errors(NULL);

	D3DXCreateEffectFromFile(Direct3D::GetInstance()->GetDevice(), "Resource\\Shader\\TexturePlaneEffect.fx", 0, 0, D3DXSHADER_DEBUG, 0, &effect, &errors);
	if (errors)
	{
		MessageBox(0,(char*)errors->GetBufferPointer(),0,0);
	}

	myCamera.BuildPerspective(D3DX_PI/3, (float)(800/600), 0.1f, 1000.0f);
	myCamera.SetViewPosition(0.0f, 0.0f, -50.0f);
}

BaseShader::~BaseShader()
{
}

BaseShader* BaseShader::GetInstance()
{
	static BaseShader instance;
	return &instance;
}

void BaseShader::InitShader(LPCSTR _fileName)
{
	ID3DXBuffer	*errors(NULL);

	D3DXCreateEffectFromFile(Direct3D::GetInstance()->GetDevice(), "Resource\\Shader\\TexturePlaneEffect.fx", 0, 0, D3DXSHADER_DEBUG, 0, &effect, &errors);
	if (errors)
	{
		MessageBox(0,(char*)errors->GetBufferPointer(),0,0);
	}
}

void BaseShader::Render(D3DXMATRIX &_matrix, IDirect3DTexture9 *_texture, Mesh &mesh)
{
	D3DXCOLOR diffuseLight = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 lightPosition = D3DXVECTOR3(0.0f, 0.0f, -10.0f);

	if(effect)
	{
		effect->SetTechnique("Basic");
		unsigned passes(0);
		effect->Begin(&passes, 0);
		for(unsigned i(0); i<passes;++i)
		{
			effect->BeginPass(i);
			{
				effect->SetMatrix("gWVP", &(_matrix * myCamera.GetViewMatrix() * myCamera.GetProjectionMatrix()));
				effect->SetMatrix("gWorld", &_matrix);

				effect->SetValue("gDiffuseLight", &diffuseLight, sizeof(D3DXCOLOR));
				effect->SetValue("gLightPosition", &lightPosition, sizeof(D3DXVECTOR3));

				effect->SetTexture("tex1", _texture);
				effect->SetBool("hasTexture", true);
				
				effect->CommitChanges();

				Direct3D::GetInstance()->GetDevice()->SetStreamSource(0, mesh.GetVertexBuffer(), 0, sizeof(TextureVertex));
				Direct3D::GetInstance()->GetDevice()->SetIndices(mesh.GetIndexBuffer());
				Direct3D::GetInstance()->GetDevice()->SetVertexDeclaration(mesh.GetVertexDeclaration());

				Direct3D::GetInstance()->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
			}
			effect->EndPass();
		}
		effect->End();
	}
}

void BaseShader::ShutdownShader()
{
	if(effect)
	{
		effect->Release();
		effect = NULL;
	}
}