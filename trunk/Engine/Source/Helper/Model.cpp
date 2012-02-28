#include "Model.h"
#include "Mesh.h"
#include <fstream>
#include <sstream>
#include <string>

using std::string;
using std::istringstream;
using std::fstream;

Model::Model()
{
}

Model::~Model()
{
}

void Model::LoadModel(const char* const filename)
{
	//This load should use our own format...
}

void Model::LoadObjModel(const char* const filename)
{
	unsigned int objCount = 0;

	std::fstream istr(filename, std::ios_base::in);
	if(!istr)
		return;

	char line[256];

	vector<float> verts;
	vector<float> texCoords;
	vector<float> normalCoords;

	vector<VertexNormalTexture> finalVerts;
	VertexNormalTexture vertexBuilder;
		
	float x,y,z;

	while( istr.getline(line,256) )
	{
		istringstream newLine(line, istringstream::in);

		string firstWord;

		newLine >> firstWord;

		if(firstWord == "#")
		{
			newLine >> firstWord;
			if(firstWord == "object")
			{
				if(verts.size()>0)
				{
					meshVec.push_back(new Mesh);
					meshVec[objCount]->InitMesh(&finalVerts[0], finalVerts.size(), D3DPT_TRIANGLELIST);

					++objCount;

					finalVerts.clear();
				}
			}
		}
		else if( firstWord == "mtllib" )
		{
		}
		else if( firstWord == "usemtl" )
		{
		}
		else if( firstWord == "v" )
		{
			newLine >> x >> y >> z;

			verts.push_back(x);
			verts.push_back(y);
			verts.push_back(z);
		}
		else if( firstWord == "vt" )
		{
			newLine >> x >> y;

			texCoords.push_back(x);
			texCoords.push_back(y);
		}
		else if( firstWord == "vn" )
		{
			newLine >> x >> y >> z;

			normalCoords.push_back(x);
			normalCoords.push_back(y);
			normalCoords.push_back(z);
		}
		else if( firstWord == "g" )
		{
		}
		else if( firstWord == "f" )
		{
			int count = 0;

			while(!newLine.eof())
			{
				count++;
				int normal = 0;
				int vertex = 0;
				int uvw = 0;
				char temp;

				newLine >> vertex;
				vertexBuilder.position = D3DXVECTOR3(verts[vertex*3-3],verts[vertex*3-2],verts[vertex*3-1]);		

				while( newLine.get(temp) )
					if(temp == '/' || temp == ' ')
						break;

				newLine >> uvw;
				vertexBuilder.u = texCoords[uvw*2-2];
				vertexBuilder.v = texCoords[uvw*2-1];

				while( newLine.get(temp) )
					if(temp == '/' || temp == ' ')
						break;

				newLine >> normal;
				vertexBuilder.normal = D3DXVECTOR3(normalCoords[normal*3-3],normalCoords[normal*3-2],normalCoords[normal*3-1]);

				finalVerts.push_back(vertexBuilder);
				
				if(count == 3)
					break;
			}
		}
	}
	
	meshVec.push_back(new Mesh);
	meshVec[objCount]->InitMesh(&finalVerts[0], finalVerts.size(), D3DPT_TRIANGLELIST);
}

void Model::CreateBox()
{
	meshVec.push_back(new Mesh);

	VertexNormalTexture verts[24];
	//FRONT
	verts[0].position = D3DXVECTOR3( -1.0f, 1.0f, -1.0f );
	verts[1].position = D3DXVECTOR3( 1.0f, 1.0f, -1.0f );
	verts[2].position = D3DXVECTOR3( 1.0f, -1.0f, -1.0f );
	verts[3].position = D3DXVECTOR3( -1.0f, -1.0f, -1.0f );

	verts[0].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
	verts[1].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
	verts[2].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
	verts[3].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );

	verts[0].u = 0.0f; verts[0].v = 0.0f;
	verts[1].u = 1.0f; verts[1].v = 0.0f; 
	verts[2].u = 1.0f; verts[2].v = 1.0f;
	verts[3].u = 0.0f; verts[3].v = 1.0f;
	
	//BACK
	verts[4].position = D3DXVECTOR3( -1.0f, 1.0f, 1.0f );
	verts[5].position = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
	verts[6].position = D3DXVECTOR3( 1.0f, -1.0f, 1.0f );
	verts[7].position = D3DXVECTOR3( -1.0f, -1.0f, 1.0f );

	verts[4].normal = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	verts[5].normal = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	verts[6].normal = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	verts[7].normal = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );

	verts[4].u = 0.0f; verts[4].v = 0.0f;
	verts[5].u = 1.0f; verts[5].v = 0.0f;
	verts[6].u = 1.0f; verts[6].v = 1.0f;
	verts[7].u = 0.0f; verts[7].v = 1.0f;

	//RIGHT
	verts[8].position = D3DXVECTOR3( 1.0f, 1.0f, -1.0f );
	verts[9].position = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
	verts[10].position = D3DXVECTOR3( 1.0f, -1.0f, 1.0f );
	verts[11].position = D3DXVECTOR3( 1.0f, -1.0f, -1.0f );

	verts[8].normal = D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
	verts[9].normal = D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
	verts[10].normal = D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
	verts[11].normal = D3DXVECTOR3( 1.0f, 0.0f, 0.0f );

	verts[8].u = 0.0f; verts[8].v = 0.0f;
	verts[9].u = 1.0f; verts[9].v = 0.0f; 
	verts[10].u = 1.0f; verts[10].v = 1.0f;
	verts[11].u = 0.0f; verts[11].v = 1.0f;

	//LEFT
	verts[12].position = D3DXVECTOR3( -1.0f, 1.0f, 1.0f );
	verts[13].position = D3DXVECTOR3( -1.0f, 1.0f, -1.0f );
	verts[14].position = D3DXVECTOR3( -1.0f, -1.0f, -1.0f );
	verts[15].position = D3DXVECTOR3( -1.0f, -1.0f, 1.0f );

	verts[12].normal = D3DXVECTOR3( -1.0f, 0.0f, 0.0f );
	verts[13].normal = D3DXVECTOR3( -1.0f, 0.0f, 0.0f );
	verts[14].normal = D3DXVECTOR3( -1.0f, 0.0f, 0.0f );
	verts[15].normal = D3DXVECTOR3( -1.0f, 0.0f, 0.0f );

	verts[12].u = 0.0f; verts[12].v = 0.0f;
	verts[13].u = 1.0f; verts[13].v = 0.0f; 
	verts[14].u = 1.0f; verts[14].v = 1.0f;
	verts[15].u = 0.0f; verts[15].v = 1.0f;

	//TOP
	verts[16].position = D3DXVECTOR3( -1.0f, 1.0f, 1.0f );
	verts[17].position = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
	verts[18].position = D3DXVECTOR3( 1.0f, 1.0f, -1.0f );
	verts[19].position = D3DXVECTOR3( -1.0f, 1.0f, -1.0f );

	verts[16].normal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	verts[17].normal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	verts[18].normal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	verts[19].normal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

	verts[16].u = 0.0f; verts[16].v = 0.0f;
	verts[17].u = 1.0f; verts[17].v = 0.0f; 
	verts[18].u = 1.0f; verts[18].v = 1.0f;
	verts[19].u = 0.0f; verts[19].v = 1.0f;

	//BOTTOM
	verts[20].position = D3DXVECTOR3( -1.0f, -1.0f, -1.0f );
	verts[21].position = D3DXVECTOR3( 1.0f, -1.0f, -1.0f );
	verts[22].position = D3DXVECTOR3( 1.0f, -1.0f, 1.0f );
	verts[23].position = D3DXVECTOR3( -1.0f, -1.0f, 1.0f );	

	verts[20].normal = D3DXVECTOR3( 0.0f, -1.0f, 0.0f );
	verts[21].normal = D3DXVECTOR3( 0.0f, -1.0f, 0.0f );
	verts[22].normal = D3DXVECTOR3( 0.0f, -1.0f, 0.0f );
	verts[23].normal = D3DXVECTOR3( 0.0f, -1.0f, 0.0f );

	verts[20].u = 0.0f; verts[20].v = 0.0f;
	verts[21].u = 1.0f; verts[21].v = 0.0f; 
	verts[22].u = 1.0f; verts[22].v = 1.0f;
	verts[23].u = 0.0f; verts[23].v = 1.0f;	

	unsigned int indexList[36] =
	{
		//FRONT
		0,1,2,
		0,2,3,

		//BACK
		6,5,4,
		6,4,7,

		//RIGHT
		8,9,10,
		8,10,11,

		//LEFT
		12,13,14,
		12,14,15,

		//TOP
		16,17,18,
		16,18,19,

		//BOTTOM
		20,21,22,
		20,22,23
	};

	meshVec[0]->InitIndexedMesh(verts, 24, indexList, 36);
}

Mesh* Model::GetMesh(unsigned int i)
{
	return meshVec[i];
}

void Model::DestroyModel()
{
	for(unsigned int i = 0; i < meshVec.size(); ++i)
	{
		meshVec[i]->DestroyMesh();
		delete meshVec[i];
	}
	meshVec.clear();
}