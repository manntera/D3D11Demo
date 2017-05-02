//==========================
//===�yModelData.cpp�z
//==========================
//    ���f���̒��_����}�e���A������ێ����܂��B
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"ModelData.h"
#include<fstream>

OGL::ModelData::ModelData()
{
}

OGL::ModelData::~ModelData()
{
}

//����������������������//
//�������ypublic�z������//
//����������������������//

//��������������������������������������������
//�������@�@�\�FRenderData���Z�b�g���܂��B
//������ ����1�FD3D11RenderData*�F�����_�����O�f�[�^
//������ ����2�Fint�F�}�e���A�����̒萔�o�b�t�@�̃X���b�g
//������   �Ԓl�Fvoid
//��������������������������������������������
bool OGL::ModelData::LoadOgmData(char* fileName)
{
	std::ifstream  ogmFile(fileName, std::ios_base::in | std::ios_base::binary);
	if (!ogmFile)
	{
		MessageBox(NULL, TEXT("ModelData::LoadOgmData �t�@�C����ǂݍ��߂Ă��܂���B"), TEXT("Err"), MB_OK);
		return false;
	}
	std::string filePass = fileName;
	filePass.erase(filePass.find_last_of('/') + 1, filePass.length());
	int temp = 0;

	ogmFile.read((char*)&temp, sizeof(int));
	std::vector<int> indexTemp;
	indexTemp.resize(temp);
	ogmFile.read((char*)&indexTemp[0], sizeof(int)*temp);
	m_indexBuffer.Create(temp, &indexTemp[0]);

	std::vector<D3DXVECTOR4> vertexTemp;
	ogmFile.read((char*)&temp, sizeof(int));
	vertexTemp.resize(temp);
	ogmFile.read((char*)&vertexTemp[0], sizeof(D3DXVECTOR4)*temp);
	m_posBuffer.Create(temp, &vertexTemp[0]);
	ogmFile.read((char*)&vertexTemp[0], sizeof(D3DXVECTOR4)*temp);
	m_normalBuffer.Create(temp, &vertexTemp[0]);
	ogmFile.read((char*)&vertexTemp[0], sizeof(D3DXVECTOR4)*temp);
	m_uvBuffer.Create(temp, &vertexTemp[0]);
	ogmFile.read((char*)&vertexTemp[0], sizeof(D3DXVECTOR4)*temp);
	m_boneIndexBuffer.Create(temp, &vertexTemp[0]);
	ogmFile.read((char*)&vertexTemp[0], sizeof(D3DXVECTOR4)*temp);
	m_boneWeightBuffer.Create(temp, &vertexTemp[0]);

	ogmFile.read((char*)&temp, sizeof(int));
	m_imageTexture.resize(temp);
	for (int i = 0; i < temp; i++)
	{
		std::string::size_type strLen;
		ogmFile.read((char*)&strLen, sizeof(std::string::size_type));
		char* name = (char*)std::malloc(strLen + 1);
		ogmFile.read(name, strLen);
		name[strLen] = '\0';
		std::string str(name);
		m_imageTexture[i].LoadFile(filePass+str);
		std::free(name);
	}

	ogmFile.read((char*)&temp, sizeof(int));
	m_materialRefVertexIndexCount.resize(temp);
	ogmFile.read((char*)&m_materialRefVertexIndexCount[0], sizeof(int)*temp);
	m_textureIndex.resize(temp);
	ogmFile.read((char*)&m_textureIndex[0], sizeof(T_TextureIndex)*temp);
	m_materialData.resize(temp);
	for (int i = 0; i < temp; i++)
	{
		T_MaterialData tempMat;
		ogmFile.read((char*)&tempMat, sizeof(T_MaterialData));
		m_materialData[i].Create(sizeof(T_MaterialData));
		m_materialData[i].SetResource(&tempMat);
	}

	ogmFile.close();
	return true;
}