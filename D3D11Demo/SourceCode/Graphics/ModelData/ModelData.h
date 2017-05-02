//==========================
//===【ModelData.h】
//==========================
//    モデルの頂点情報やマテリアル情報を保持します。
//==========================
#pragma	once
//=====================//
//===【インクルード記述】 ===//
//=====================//
#include<vector>
#include"../D3D11Device/D3D11Device.h"
#include"IndexBuffer\IndexBuffer.h"
#include"VertexBuffer\VertexBuffer.h"
namespace	OGL
{
	class VertexBuffer;
	class IndexBuffer;
	class ConstantBuffer;

	class	ModelData
	{
	public:
		bool LoadOgmData(char* fileName);
	private:
		struct T_TextureIndex
		{
			int diffuse;
			int toon;
			int addSphere;
			int mulSphere;
		};
		struct T_MaterialData
		{
			D3DXVECTOR4 diffuse;
			D3DXVECTOR4 specular;		//wはPower
			D3DXVECTOR4	ambient;
		};
	public:
		IndexBuffer		m_indexBuffer;
		VertexBuffer	m_posBuffer;
		VertexBuffer	m_normalBuffer;
		VertexBuffer	m_uvBuffer;
		VertexBuffer	m_boneIndexBuffer;
		VertexBuffer	m_boneWeightBuffer;
		std::vector<ImageTexture>	m_imageTexture;
		std::vector<int>	m_materialRefVertexIndexCount;
		std::vector<T_TextureIndex>	m_textureIndex;
		std::vector<ConstantBuffer> m_materialData;
	public:
		ModelData();
		~ModelData();

	};	//EndOf__class_ModelData
}	//EndOf__namespace_OGL
