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
	//Load a 3D model
	
	//meshVec.push_back(new Mesh);

	//Load in every mesh into vector
}

void Model::LoadObjModel(const char* const filename)
{
	meshVec.push_back(new Mesh);

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
			newLine >> x >> y >> z;

			texCoords.push_back(x);
			texCoords.push_back(y);
			texCoords.push_back(z);
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
				vertexBuilder.u = texCoords[uvw*3-3];
				vertexBuilder.v = texCoords[uvw*3-2];

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
	
	meshVec[0]->InitMesh(&finalVerts[0], finalVerts.size(), D3DPT_TRIANGLELIST);
}

void CreatePrimitive(PrimitiveType type)
{
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